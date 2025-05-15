//
// Created by belyashik2k on 5/10/25.
//

#include "presentation/imgui/views/game/ImguiSudokuGameSummaryView.h"

#include "application/presenters/game/SudokuGameSummaryPresenter.h"
#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiChildWindowGuard.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"
#include "presentation/imgui/managers/ImguiAudioManager.h"

void ImguiSudokuGameSummaryView::render() {
    ImguiWindowGuard window(
        "Game Summary Menu",
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
    );
    ImguiUtils::updateBackground("../assets/textures/menu/leaderboard.jpg");

    if (presenter->getNeedToPlaySound()) {
        ImguiAudioManager::getInstance().playAudio("../assets/sounds/win.wav");
    }

    const auto &areaSize = ImVec2(ImGui::GetWindowSize().x * 0.30f, ImGui::GetWindowSize().y * 0.40f);
    ImguiChildWindowGuard tableArea(
        "SummaryArea",
        areaSize,
        ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
        true
    );

    ImguiUtils::printText("Game Summary", BLACK, 39, true);
    ImguiUtils::addVerticalSpacing(4);

    std::string difficulty = presenter->getDifficulty();
    int mistakesCount = presenter->getMistakesCount();
    std::string elapsedTime = presenter->getElapsedTime();
    int gainedRating = presenter->getGainedRating();

    const std::string difficultyStr = std::format(
        "Difficulty: {}",
        difficulty
    );
    const std::string mistakesCountStr = std::format(
        "Mistakes count: {}",
        mistakesCount
    );
    const std::string elapsedTimeStr = std::format(
        "Elapsed time: {}",
        elapsedTime
    );
    const std::string gainedRatingStr = std::format(
        "You gained {} rating",
        gainedRating
    );

    ImguiUtils::printText(difficultyStr.c_str(), BLACK, 35, true);
    ImguiUtils::addVerticalSpacing(2);
    ImguiUtils::printText(mistakesCountStr.c_str(), BLACK, 35, true);
    ImguiUtils::addVerticalSpacing(2);
    ImguiUtils::printText(elapsedTimeStr.c_str(), BLACK, 35, true);
    ImguiUtils::addVerticalSpacing(2);
    ImguiUtils::printText(gainedRatingStr.c_str(), BLACK, 35, true);

    ImguiUtils::addVerticalSpacing(4);

    ImguiUtils::createButton(
            "finish_button",
            "Finish game",
            ImVec2(ImGui::GetWindowSize().x, 60),
            [this] {
                presenter->onFinishGameButtonClicked();
            }
        );
}
