//
// Created by belyashik2k on 5/3/25.
//

#include "views/imgui/profile/ImguiProfileView.h"

#include "views/imgui/ImguiWindow.h"

void ImguiProfileView::render() {
    ImguiWindow window("Profile", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");
}
