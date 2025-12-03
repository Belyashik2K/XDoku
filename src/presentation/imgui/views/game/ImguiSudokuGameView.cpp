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

#include <format>

#include "presentation/imgui/managers/ImguiAudioManager.h"

void ImguiSudokuGameView::render() {
    ImguiWindowGuard window("Game Menu",
                            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/game/background.png");

    if (!presenter->getCurrentGame()) {
        ImguiUtils::printText("No active game found", BLACK, 30, true);
        return;
    }

    renderLoading();
    renderGame();
}

void ImguiSudokuGameView::renderGame() const {
    ImguiStyleColorGuard localColorGuard({
        {ImGuiCol_WindowBg, TRANSPARENT}
    });

    const ImVec2 windowSize = ImGui::GetWindowSize();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.55f, windowSize.y)); {
        ImguiWindowGuard gridArea(
            "GridArea",
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        );
        renderSudokuGrid();
    }

    ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.55f, 0));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.45f, windowSize.y));
    {
        ImguiWindowGuard gridArea(
            "StatisticsArea",
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        );
        renderStatistics();
        renderButtons();
    }
}

void ImguiSudokuGameView::renderLoading() const {
    if (presenter->getLoadingStatus() != LOADING) return;
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
    const auto grid = presenter->getCurrentGame()->getCurrentGrid();
    auto [selectedRow, selectedCol] = presenter->getSelectedCell();

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
                presenter->setSelectedCell(row, col);
            }

            if (row == selectedRow && col == selectedCol) {
                if (presenter->isValidMove()) {
                    drawList->AddRectFilled(cellMin, cellMax, VERY_LIGHT_GRAY);
                } else {
                    drawList->AddRectFilled(cellMin, cellMax, LIGHT_RED);
                }
            }

            if (!grid.isCellEmpty(row, col)) {
                char text[2];
                std::snprintf(text, sizeof(text), "%d", grid.getCellValue(row, col));
                const ImVec2 textSize = ImGui::CalcTextSize(text);
                auto textPos = ImVec2(
                    cellMin.x + (cellSize - textSize.x) * 0.5f,
                    cellMin.y + (cellSize - textSize.y) * 0.5f
                );
                drawList->AddText(textPos, BLACK, text);
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
    if (presenter->getLoadingStatus() != LOADED) return;

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
        auto [fst, snd] = presenter->getSelectedCell();
        const int selectedRow = fst;
        const int selectedCol = snd;
        if (selectedRow < 0 || selectedCol < 0) {
            return;
        }

        for (int key = ImGuiKey_1; key <= ImGuiKey_9; ++key) {
            if (ImGui::IsKeyPressed(static_cast<ImGuiKey>(key))) {
                const int value = key - ImGuiKey_0;
                if (const bool result = presenter->onNewMove(value); !result) {
                    ImguiAudioManager::getInstance().playAudio("../assets/sounds/incorrect.wav");
                } else {
                    ImguiAudioManager::getInstance().playAudio("../assets/sounds/correct.wav");
                }
            }
        }

        if (
            ImGui::IsKeyPressed(ImGuiKey_Escape)
        ) {
            presenter->unselectCell();
        }
    }
}

void ImguiSudokuGameView::renderButtons() const {
    const auto windowSize = ImGui::GetWindowSize();
    const auto buttonSize = ImVec2(windowSize.x * 0.5f, 70);

    {
        ImguiStyleColorGuard localStyleGuard({
            {ImGuiCol_Button, LIGHT_RED},
            {ImGuiCol_Text, BLACK},
            {ImGuiCol_Border, BLACK},
        });
        ImGui::SetCursorPosX((windowSize.x - buttonSize.x) / 2);
        ImguiUtils::createButton(
            "surrender_button",
            "Surrender :(",
            buttonSize,
            [this] {
                presenter->onSurrenderButtonClicked();
        });

        ImguiUtils::addVerticalSpacing(3);
    }
    {
        ImGui::SetCursorPosX((windowSize.x - buttonSize.x) / 2);
        ImguiUtils::createButton(
            "back_button",
            "Back to menu",
            buttonSize,
            [this] {
                presenter->onBackButtonClicked();
        });
    }

}

void ImguiSudokuGameView::renderStatistics() const {
    if (!presenter->getCurrentGame()) return;
    ImGui::SetCursorPosY(ImGui::GetWindowSize().y * 0.33f);
    ImguiUtils::printText("Statistics", BLACK, 39, true);
    ImguiUtils::addVerticalSpacing(3);

    const std::string difficulty = std::format(
        "Difficulty: {}",
        presenter->getGameStatus()
    );
    const std::string mistakes = std::format(
        "Mistakes: {}",
        presenter->getMistakesCount()
    );
    const std::string elapsedTime = std::format(
        "Elapsed time: {}",
        presenter->getElapsedTime()
    );

    ImguiUtils::printText(difficulty.c_str(), BLACK, 30, true);
    ImguiUtils::addVerticalSpacing(3);
    ImguiUtils::printText(mistakes.c_str(), BLACK, 30, true);
    ImguiUtils::addVerticalSpacing(3);
    ImguiUtils::printText(elapsedTime.c_str(), BLACK, 30, true);
    ImguiUtils::addVerticalSpacing(6);
}
