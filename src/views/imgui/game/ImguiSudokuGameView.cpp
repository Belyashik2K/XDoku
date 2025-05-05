//
// Created by belyashik2k on 5/3/25.
//

#include "views/imgui/game/ImguiSudokuGameView.h"

#include "views/imgui/ImguiView.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSudokuGameView::render() {
    ImguiWindow window("Game Menu",
                       ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");
}
