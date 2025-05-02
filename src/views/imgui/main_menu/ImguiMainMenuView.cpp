//
// Created by belyashik2k on 5/2/25.
//

#include "views/imgui/ImguiWindow.h"
#include "views/imgui/main_menu/ImguiMainMenuView.h"

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiColors.h"
#include "views/imgui/ImguiStyleColorGuard.h"
#include "views/imgui/ImguiStyleVarGuard.h"

void ImguiMainMenuView::render() {
    ImguiWindow window("Main Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
    {
        updateBackground("../assets/textures/menu/background.jpg");
        renderMainMenu();
    }
}

void ImguiMainMenuView::renderMainMenu() const {
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float menuAreaWidth = windowSize.x * 0.58f;
    const float menuAreaHeight = windowSize.y;
    const ImVec2 menuAreaSize(menuAreaWidth, menuAreaHeight);

    ImguiChildWindow menuArea(
        "MenuArea",
        menuAreaSize,
        ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
        false
    );

    {
        const ImVec2 menuSize = ImGui::GetWindowSize();
        const float childWidth = menuSize.x * 0.75f;
        const float childHeight = menuSize.y * 0.36f;
        const ImVec2 childSize(childWidth, childHeight);

        ImguiChildWindow menuPos(
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

    createButton(
        "play_button",
        "Play",
        buttonSize,
        [this] {
            presenter->onPlayButtonClicked();
        }
    );
    createButton(
        "profile_button",
        "Profile",
        buttonSize,
        [this] {
            presenter->onProfileButtonClicked();
        }
    );
    createButton(
        "leaderboard_button",
        "Leaderboard",
        buttonSize,
        [this] {
            presenter->onLeaderboardButtonClicked();
        }
    );
    createButton(
        "how_to_play_button",
        "How to play",
        buttonSize,
        [this] {
            presenter->onHowToPlayButtonClicked();
        }
    );
}
