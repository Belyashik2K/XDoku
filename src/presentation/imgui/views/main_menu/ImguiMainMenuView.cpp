//
// Created by belyashik2k on 5/2/25.
//

#include "application/presenters/MainMenuPresenter.h"
#include "presentation/imgui/views/main_menu/ImguiMainMenuView.h"
#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiChildWindowGuard.h"
#include "presentation/imgui/guards/ImguiStyleColorGuard.h"
#include "presentation/imgui/guards/ImguiStyleVarGuard.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"
#include "presentation/imgui/managers/ImguiFontManager.h"

void ImguiMainMenuView::render() {
    ImguiWindowGuard window("Main Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");
    renderMainMenu();
}

void ImguiMainMenuView::renderMainMenu() const {
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
        const float childHeight = menuSize.y * 0.43f;
        const ImVec2 childSize(childWidth, childHeight);

        ImguiChildWindowGuard menuPos(
            "MenuPos",
            childSize,
            ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
            true
        );

        renderFormButtons();
    }

}

void ImguiMainMenuView::renderFormButtons() const {
    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f},
        {ImGuiStyleVar_ItemSpacing, ImVec2(0.0, 15.0f)},
    });

    const auto &buttonSize = ImVec2(ImGui::GetWindowSize().x, 70);

    ImguiStyleColorGuard mainMenuButtons({
            {ImGuiCol_Text, WHITE},
            {ImGuiCol_Border, WHITE},
            {ImGuiCol_Button, GRAY},
    });
    ImGui::PushFont(ImguiFontManager::getInstance().getFont(30));
    ImguiUtils::createButton(
        "play_button",
        "Play",
        buttonSize,
        [this] {
            presenter->onPlayButtonClicked();
        }
    );
    ImguiUtils::createButton(
        "profile_button",
        "Profile",
        buttonSize,
        [this] {
            presenter->onProfileButtonClicked();
        }
    );
    ImguiUtils::createButton(
        "leaderboard_button",
        "Leaderboard",
        buttonSize,
        [this] {
            presenter->onLeaderboardButtonClicked();
        }
    );
    ImguiUtils::createButton(
        "how_to_play_button",
        "How to play",
        buttonSize,
        [this] {
            presenter->onHowToPlayButtonClicked();
        }
    );
    ImguiUtils::createButton(
        "exit_button",
        "Exit",
        buttonSize,
        [this] {
            presenter->onExitButtonClicked();
        }
    );
    ImGui::PopFont();
}
