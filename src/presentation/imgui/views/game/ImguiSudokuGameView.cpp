//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/game/SudokuGamePresenter.h"
#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiChildWindowGuard.h"
#include "presentation/imgui/guards/ImguiStyleColorGuard.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"
#include "presentation/imgui/managers/ImguiFontManager.h"
#include "presentation/imgui/views/game/ImguiSudokuGameView.h"

void ImguiSudokuGameView::render() {
    ImguiWindowGuard window("Game Menu",
                            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/game/background.png");

    auto sp = getPresenter();
    if (!sp) return;

    renderLoading();
    renderGame();
}

void ImguiSudokuGameView::renderGame() const {
    ImguiStyleColorGuard localColorGuard({
        {ImGuiCol_WindowBg, TRANSPARENT}
    });

    const ImVec2 windowSize = ImGui::GetWindowSize();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.7f, windowSize.y));
    {
        ImguiWindowGuard gridArea(
            "GridArea",
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        );
        renderSudokuGrid();
    }

    ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.7f, 0));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.3f, windowSize.y));
    {
        ImguiWindowGuard gridArea(
            "StatisticsArea",
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        );
        renderStatistics();
    }
}

void ImguiSudokuGameView::renderLoading() const {
    const auto sp = getPresenter();
    if (!sp) return;
    if (sp->getLoadingStatus() != LOADING) return;
    ImguiUtils::printText("Loading...", BLACK, 30, true);
}

void ImguiSudokuGameView::drawGridLines(
    const ImVec2 windowPos,
    const float gridSize,
    const float cellSize,
    ImDrawList *drawList
) {
    for (int i = 0; i <= 9; ++i) {
        const float x = windowPos.x + static_cast<float>(i) * cellSize;
        const float y = windowPos.y + static_cast<float>(i) * cellSize;

        float thickness;
        if (i == 0 || i == 9) {
            thickness = 5.5f;
        } else if (i % 3 == 0) {
            thickness = 4.0f;
        } else {
            thickness = 1.0f;
        }

        constexpr float gap = 1.25f;
        drawList->AddLine(
            ImVec2(x, windowPos.y - gap), ImVec2(x, windowPos.y + gridSize + gap),
            BLACK, thickness
        );
        drawList->AddLine(
            ImVec2(windowPos.x - gap, y), ImVec2(windowPos.x + gridSize + gap, y),
            BLACK, thickness
        );
    }
}

void ImguiSudokuGameView::drawCells(
    const ImVec2 &windowPos,
    const float cellSize,
    ImDrawList *drawList
) const {
    const auto sp = getPresenter();
    if (!sp) return;

    const auto grid = sp->getCurrentGame()->getCurrentGrid();
    auto [selectedRow, selectedCol] = sp->getSelectedCell();

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            auto cellMin = ImVec2(
                windowPos.x + static_cast<float>(col) * cellSize,
                windowPos.y + static_cast<float>(row) * cellSize
            );
            auto cellMax = ImVec2(cellMin.x + cellSize, cellMin.y + cellSize);

            ImGui::InvisibleButton(
                ("Cell" + std::to_string(row * 9 + col)).c_str(),
                ImVec2(cellSize, cellSize)
            );
            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
                sp->setSelectedCell(row, col);
            }

            if (row == selectedRow && col == selectedCol) {
                drawList->AddRectFilled(cellMin, cellMax, VERY_LIGHT_GRAY);
            }

            if (!grid.isCellEmpty(row, col)) {
                std::string text = std::to_string(grid.getCellValue(row, col));
                const ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
                auto textPos = ImVec2(
                    cellMin.x + (cellSize - textSize.x) * 0.5f,
                    cellMin.y + (cellSize - textSize.y) * 0.5f
                );
                drawList->AddText(textPos, BLACK, text.c_str());
            }

            ImGui::SetCursorScreenPos(ImVec2(cellMax.x, cellMin.y));
        }
        ImGui::SetCursorScreenPos(ImVec2(windowPos.x, windowPos.y + (static_cast<float>(row) + 1.0f) * cellSize));
    }
}

void ImguiSudokuGameView::adjustLayoutParameters(ImVec2 &windowPos, ImVec2 &windowSize) {
    windowPos.x = windowPos.x + 5.0f;
    windowPos.y = windowPos.y + 5.0f;
    windowSize.x = windowSize.x - 15.0f;
    windowSize.y = windowSize.y - 15.0f;
}

void ImguiSudokuGameView::renderSudokuGrid() const {
    const auto sp = getPresenter();
    if (!sp) return;
    if (sp->getLoadingStatus() != LOADED) return;

    const ImVec2 parentWindowSize = ImGui::GetWindowSize();
    ImguiChildWindowGuard gridArea(
        "Grid",
        ImVec2(parentWindowSize.x * 0.70f, parentWindowSize.y * 0.70f),
        ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
        true
    );

    ImVec2 windowPos = ImGui::GetCursorScreenPos();
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    adjustLayoutParameters(windowPos, windowSize);

    const float gridSize = std::min(windowSize.x, windowSize.y);
    const float cellSize = gridSize / 9.0f;
    ImDrawList *drawList = ImGui::GetWindowDrawList();

    ImGui::PushFont(ImguiFontManager::getInstance().getFont(39));
    drawGridLines(windowPos, gridSize, cellSize, drawList);
    drawCells(windowPos, cellSize, drawList);
    handleKeyboardInput();
    ImGui::PopFont();
}

void ImguiSudokuGameView::handleKeyboardInput() const {
    if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)) {
        const auto sp = getPresenter();
        if (!sp) return;
        auto [fst, snd] = getPresenter()->getSelectedCell();
        const int selectedRow = fst;
        const int selectedCol = snd;
        if (selectedRow < 0 || selectedCol < 0) {
            return;
        }

        for (int key = ImGuiKey_1; key <= ImGuiKey_9; ++key) {
            if (ImGui::IsKeyPressed(static_cast<ImGuiKey>(key))) {
                const int value = key - ImGuiKey_0;
                printf("Key pressed: %d on cell (%d, %d)\n", value, selectedRow, selectedCol);
                sp->onNewMove(value);
            }
        }

        if (
            ImGui::IsKeyPressed(ImGuiKey_Escape)
        ) {
            printf("Key pressed: ESC on cell (%d, %d)\n", selectedRow, selectedCol);
            sp->setSelectedCell(-1, -1);
        }
    }
}

void ImguiSudokuGameView::renderStatistics() const {
    const auto sp = getPresenter();
    if (!sp) return;
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.45f);
    ImguiUtils::printText("Statistics", BLACK, 30, true);
    ImguiUtils::addVerticalSpacing(3);

    const std::string difficulty = std::format(
        "Difficulty: {}",
        sp->getGameStatus()
    );
    const std::string mistakes = std::format(
        "Mistakes: {}",
        sp->getMistakesCount()
    );
    const std::string elapsedTime = std::format(
        "Elapsed time: {}",
        sp->getElapsedTime()
    );

    ImguiUtils::printText(difficulty.c_str(), BLACK, 28, true);
    ImguiUtils::addVerticalSpacing(3);
    ImguiUtils::printText(mistakes.c_str(), BLACK, 28, true);
    ImguiUtils::addVerticalSpacing(3);
    ImguiUtils::printText(elapsedTime.c_str(), BLACK, 28, true);
}
