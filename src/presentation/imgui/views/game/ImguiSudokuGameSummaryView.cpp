//
// Created by belyashik2k on 5/10/25.
//

#include "presentation/imgui/views/game/ImguiSudokuGameSummaryView.h"

#include "application/presenters/game/SudokuGameSummaryPresenter.h"
#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiSudokuGameSummaryView::render() {
    ImguiWindowGuard window(
        "Game Summary Menu",
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
    );
    ImguiUtils::updateBackground("../assets/textures/menu/leaderboard.jpg");
    ImguiUtils::printText("Game Summary", BLACK, 39, true);
    ImguiUtils::createButton(
            "finish_button",
            "Finish game",
            ImVec2(ImGui::GetWindowSize().x, 60),
            [this] {
                const auto sp = getPresenter();
                if (!sp) return;
                sp->onFinishGameButtonClicked();
            }
        );
}
