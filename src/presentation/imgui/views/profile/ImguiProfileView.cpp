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
        const float childHeight = menuSize.y * 0.43f;
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
    const std::string  playerID = std::format(R"(Your ID: {})", user->getId());
    const std::string username = std::format(R"(Username: @{})", user->getUsername());
    const std::string email = std::format(R"(Email: {})", user->getEmail());
    const std::string rating = std::format(R"(Current rating: {} points)", user->getRating());

    ImguiUtils::printText(header, BLACK, 38, true);
    ImguiUtils::addVerticalSpacing(6);
    ImguiUtils::printText(playerID.c_str(), BLACK, 35, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(username.c_str(), BLACK, 35, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(email.c_str(), BLACK, 35, false);
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText(rating.c_str(), BLACK, 35, false);
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
