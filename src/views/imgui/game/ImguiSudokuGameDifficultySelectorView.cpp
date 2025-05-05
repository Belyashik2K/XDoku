//
// Created by belyashik2k on 5/3/25.
//

#include "views/imgui/game/ImguiSudokuGameDifficultySelectorView.h"

#include "views/imgui/ImguiWindow.h"

void ImguiSudokuGameDifficultySelectorView::render() {
    ImguiWindow window("Diff Selector Menu",
                           ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");
}
