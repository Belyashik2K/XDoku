//
// Created by belyashik2k on 5/2/25.
//

#include "views/imgui/ImguiWindow.h"
#include "views/imgui/main_menu/ImguiMainMenuView.h"

void ImguiMainMenuView::render() {
    ImguiWindow window("Main Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
    {
        updateBackground("../assets/textures/background.jpg");
        printText("XDoku", ImColor(0, 0, 0), 28, true);
        // addVerticalSpacing(6);
    }
}
