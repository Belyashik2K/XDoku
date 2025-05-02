//
// Created by Belyashik2K on 02.05.2025.
//

#include "views/imgui/leaderboard/ImguiLeaderboardView.h"

#include "managers/FontManager.h"
#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiColors.h"
#include "views/imgui/ImguiStyleColorGuard.h"
#include "views/imgui/ImguiStyleVarGuard.h"
#include "views/imgui/ImguiWindow.h"

void ImguiLeaderboardView::render() {
    ImguiWindow window("Main Menu",
                       ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    updateBackground("../assets/textures/menu/leaderboard.jpg");
    printLoader();
    renderLeaderboard();
}

void ImguiLeaderboardView::printLoader() const {
    if (!presenter->isOnLoading()) return;

    ImGui::SetCursorPosY(ImGui::GetWindowHeight() * 0.45f);
    printText("Loading...", BLACK, 39, true);
}

void ImguiLeaderboardView::renderLeaderboard() const {
    if (presenter->isOnLoading()) return;

    const LeaderboardPlaces leaderboardPlaces = presenter->getLeaderboardPlaces();
    if (!leaderboardPlaces.has_value()) {
        printText("No leaderboard data available :(", BLACK, 39, true);
        return;
    }

    const auto &areaSize = ImVec2(ImGui::GetWindowSize().x * 0.30f, ImGui::GetWindowSize().y * 0.60f);
    ImguiChildWindow tableArea(
        "TableArea",
        areaSize,
        ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
        true
    );

    printText("Leaderboard", BLACK, 33, true);
    addVerticalSpacing(4);

    // TODO: Center text in rows
    ImGui::PushFont(FontManager::getInstance().getFont(33));
    ImGui::BeginTable("Leaderboard Table", 3, ImGuiTableFlags_RowBg);
    ImGui::TableSetupColumn("Place", ImGuiTableColumnFlags_WidthFixed, areaSize.x * 0.05f);
    ImGui::TableSetupColumn("Username", ImGuiTableColumnFlags_WidthFixed, areaSize.x * 0.55f);
    ImGui::TableSetupColumn("Current rating", ImGuiTableColumnFlags_WidthFixed, areaSize.x * 0.40f);
    for (const auto &place : leaderboardPlaces.value()) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("%d.", place.getPlace());
        ImGui::TableSetColumnIndex(1);
        ImGui::Text("@%s", place.getUsername().c_str());
        ImGui::TableSetColumnIndex(2);
        ImGui::Text("%d points", place.getRating());
    }
    ImGui::EndTable();
    ImGui::PopFont();

    addVerticalSpacing(4);

    {
        ImguiStyleVarGuard localVarGuard({
            {ImGuiStyleVar_FrameRounding, 10.0f},
            {ImGuiStyleVar_FrameBorderSize, 1.0f},
        });
        ImguiStyleColorGuard mainMenuButtons({
             {ImGuiCol_Text, WHITE},
             {ImGuiCol_Border, WHITE},
             {ImGuiCol_Button, GRAY},
         });

        createButton(
            "refresh_button",
            "Refresh",
            ImVec2(ImGui::GetWindowSize().x, 60),
            [this] {
                presenter->onRefreshButtonClicked();
            }
        );
        addVerticalSpacing();
        createButton(
            "back_button",
            "Back to menu",
            ImVec2(ImGui::GetWindowSize().x, 60),
            [this] {
                presenter->onBackButtonClicked();
            }
        );
    }
}

