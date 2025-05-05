//
// Created by belyashik2k on 5/3/25.
//

#include "presentation/imgui/views/game/ImguiSudokuGameView.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiSudokuGameView::render(){
    ImguiWindowGuard window("Game Menu",
                       ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);
    ImguiUtils::updateBackground("../assets/textures/menu/background.jpg");
}
