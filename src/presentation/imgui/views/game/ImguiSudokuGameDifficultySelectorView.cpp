//
// Created by belyashik2k on 5/3/25.
//

#include "domain/sudoku/enums/SudokuDifficulty.h"
#include "application/presenters/game/SudokuGameDifficultySelectorPresenter.h"
#include "presentation/imgui/views/game/ImguiSudokuGameDifficultySelectorView.h"

#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiChildWindowGuard.h"
#include "presentation/imgui/guards/ImguiStyleColorGuard.h"
#include "presentation/imgui/guards/ImguiStyleVarGuard.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiSudokuGameDifficultySelectorView::render() {
    ImguiWindowGuard window(
        "Diff Selector Menu",
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
    );
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");

    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float menuAreaWidth = windowSize.x * 0.58f;
    const float menuAreaHeight = windowSize.y;
    const ImVec2 menuAreaSize(menuAreaWidth, menuAreaHeight);

    ImguiChildWindowGuard menuArea(
        "MenuArea",
        menuAreaSize,
        ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
        false
    );
    {
        const ImVec2 menuSize = ImGui::GetWindowSize();
        const float childWidth = menuSize.x * 0.75f;
        const float childHeight = menuSize.y * 0.38f;
        const ImVec2 childSize(childWidth, childHeight);

        ImguiChildWindowGuard menuPos(
            "MenuPos",
            childSize,
            ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
            true
        );

        renderHeader();
        renderDifficultyButtons();
    }
}

void ImguiSudokuGameDifficultySelectorView::renderHeader() {
    ImguiUtils::printText(
        "Select sudoku difficulty",
        BLACK,
        35,
        true
    );
    ImguiUtils::addVerticalSpacing(3);
}


void ImguiSudokuGameDifficultySelectorView::renderDifficultyButtons() const {
    const float xSize = ImGui::GetWindowSize().x;

    {
        ImguiStyleVarGuard localVarGuard({
            {ImGuiStyleVar_ItemSpacing, ImVec2(0.0, 15.0f)},
        });
        int i = 0;
        for (auto &difficulty : SudokuDifficulty::getDifficultyNames()) {
            const bool isOdd = ++i % 2 != 0;
            const bool isNotLast = i != SudokuDifficulty::getDifficultyNames().size();
            const float width = isNotLast ? xSize * 0.5f : xSize;
            const std::string copy = difficulty;
            std::transform(difficulty.begin(), difficulty.begin() + 1, difficulty.begin(), toupper);
            ImguiUtils::createButton(
                difficulty.c_str(),
                difficulty.c_str(),
                ImVec2(width, 70),
                [this, copy] {
                    const auto sp = getPresenter();
                    if (!sp) return;
                    sp->onDifficultySelected(SudokuDifficulty::fromString(copy));
                }
            );
            if (isOdd && isNotLast) {
                ImGui::SameLine();
            }
        }
    }

    {
        ImguiUtils::createButton(
        "back_button",
        "Back to menu",
        ImVec2(xSize, 70),
        [this] {
            const auto sp = getPresenter();
            if (!sp) return;
            sp->onBackButtonClicked();
        }
        );
    }
}
