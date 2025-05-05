//
// Created by belyashik2k on 5/3/25.
//

#include "views/imgui/how_to_play/ImguiHowToPlayView.h"

#include "views/imgui/ImguiView.h"
#include "views/imgui/ImguiWindow.h"

void ImguiHowToPlayView::render() {
    ImguiWindow window("How to play",
                       ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");
}
