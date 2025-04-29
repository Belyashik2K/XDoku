//
// Created by belyashik2k on 4/29/25.
//

#include "views/imgui/sign_up/ImguiSignUpView.h"

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSignUpView::render() {
    ImguiWindow window("Sign up Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove );
    updateBackground("../assets/textures/background.jpg");
}
