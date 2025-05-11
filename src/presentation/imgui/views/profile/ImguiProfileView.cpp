//
// Created by belyashik2k on 5/3/25.
//

#include "presentation/imgui/views/profile/ImguiProfileView.h"

#include "application/presenters/ProfilePresenter.h"
#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiChildWindowGuard.h"
#include "presentation/imgui/guards/ImguiStyleVarGuard.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiProfileView::render() {
    ImguiWindowGuard window(
        "Profile", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
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
    ); {
        const ImVec2 menuSize = ImGui::GetWindowSize();
        const float childWidth = menuSize.x * 0.5f;
        const float childHeight = menuSize.y * 0.66f;
        const ImVec2 childSize(childWidth, childHeight);

        ImguiChildWindowGuard menuPos(
            "MenuPos",
            childSize,
            ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
            true
        );

        renderStatistics();
        renderButtons();
    }
}

void ImguiProfileView::renderStatistics() const {
    const auto sp = getPresenter();
    if (!sp) return;

    const User *user = sp->getCurrentUser();

    const auto header = "Profile";
    const std::string playerID = std::format(R"(Your ID: {})", user->getId());
    const std::string username = std::format(R"(Username: @{})", user->getUsername());
    const std::string email = std::format(R"(Email: {})", user->getEmail());
    const std::string rating = std::format(R"(Current rating: {} points)", user->getRating());

    const auto stats = "Statistics";
    const std::string totalGames = std::format(R"(Total games: {})", sp->getGamesCount());
    const std::string totalWins = std::format(R"(Total finished: {})", sp->getFinishedGamesCount());
    const std::string totalCompletion = std::format(R"(Total completion: {}%%)", sp->getCompletionRate());
    const std::string averageTimeValue = sp->getAverageSolutionTime();
    const std::string averageTime = std::format(R"(Average time: {})", averageTimeValue);
    const std::string mostCommonDifficulty =
            std::format(R"(Most common difficulty: {})", sp->getMostCommonDifficulty());

    constexpr int headerPx = 36;
    constexpr int textPx = 32;

    ImguiUtils::printText(header, BLACK, headerPx, true);
    ImguiUtils::addVerticalSpacing(6);
    ImguiUtils::printText(playerID.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(username.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(email.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(rating.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing(6);
    ImguiUtils::printText(stats, BLACK, headerPx, true);
    ImguiUtils::addVerticalSpacing(6);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(totalGames.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(totalWins.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(totalCompletion.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(averageTime.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(mostCommonDifficulty.c_str(), BLACK, textPx, false);
    ImguiUtils::addVerticalSpacing(6);
}

void ImguiProfileView::renderButtons() const {
    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_ItemSpacing, ImVec2(0.0, 15.0f)},
    });

    const auto &buttonSize = ImVec2(ImGui::GetWindowSize().x, 70);
    ImguiUtils::createButton(
        "logout_button",
        "Logout",
        buttonSize,
        [this] {
            const auto sp = getPresenter();
            if (!sp) return;
            sp->onLogoutButtonClicked();
        }
    );
    ImguiUtils::createButton(
        "back_button",
        "Back to menu",
        buttonSize,
        [this] {
            const auto sp = getPresenter();
            if (!sp) return;
            sp->onBackButtonClicked();
        }
    );
}
