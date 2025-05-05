//
// Created by belyashik2k on 5/3/25.
//

#include "presentation/imgui/views/profile/ImguiProfileView.h"

#include "application/presenters/ProfilePresenter.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiProfileView::render() {
    ImguiWindowGuard window("Profile", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");

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

