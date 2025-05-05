//
// Created by belyashik2k on 5/3/25.
//

#include "presentation/imgui/views/how_to_play/ImguiHowToPlayView.h"

#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiHowToPlayView::render() {
    ImguiWindowGuard window("How to play",
                       ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");
}
