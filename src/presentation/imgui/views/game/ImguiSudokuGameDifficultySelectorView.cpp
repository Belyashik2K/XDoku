//
// Created by belyashik2k on 5/3/25.
//

#include "presentation/imgui/views/game/ImguiSudokuGameDifficultySelectorView.h"

#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiSudokuGameDifficultySelectorView::render() {
    ImguiWindowGuard window("Diff Selector Menu",
                           ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");
}
