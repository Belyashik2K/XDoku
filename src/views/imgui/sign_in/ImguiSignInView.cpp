//
// Created by belyashik2k on 4/27/25.
//

#include "views/imgui/sign_in/ImguiSignInView.h"

#include <imgui.h>

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiStyleColorGuard.h"
#include "views/imgui/ImguiStyleVarGuard.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSignInView::render() {
    ImguiWindow window("Login Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); {
        updateBackground("../assets/textures/background.jpg");
        renderLoginForm();
    }
}

void ImguiSignInView::renderLoginForm() {
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float childWidth = windowSize.x / 3;
    const float childHeight = windowSize.y / 3;
    const ImVec2 childSize(childWidth, childHeight);

    ImguiChildWindow childWindow(
        "CenteredChild",
        childSize,
        ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
        true
    );

    renderFormHeader();
    renderFormInputs();
    renderFormButtons();
}

void ImguiSignInView::renderFormHeader() {
    const auto headerText = "Sign in to XDoku";
    printText(headerText, true);
    addVerticalSpacing(6);
}

void ImguiSignInView::renderFormInputs() const {
    ImguiStyleColorGuard localColorGuard({
        {ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
        {ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)}
    });

    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FramePadding, ImVec2(15.0f, 15.0f)},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const ImVec2 childSize = ImGui::GetWindowSize();
    ImGui::PushItemWidth(childSize.x);
    // printText("Username", false); -> TODO: add ability to change color of text and size
    addVerticalSpacing();
    createInputField(
        "username_input",
        "Username",
        presenter->getUsername(),
        presenter->getBufferSize(),
        ImGuiInputTextFlags_CharsNoBlank
    );
    addVerticalSpacing();
    createInputField(
        "password_input",
        "Password",
        presenter->getPassword(),
        presenter->getBufferSize(),
        ImGuiInputTextFlags_Password,
        true
    );
    ImGui::PopItemWidth();

    addVerticalSpacing(6);
}

void ImguiSignInView::renderFormButtons() const {
    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f}
    });
    ImguiStyleColorGuard localColorGuard({
        {ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
        {ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)}
    });

    const ImVec2 childSize = ImGui::GetWindowSize();
    const auto &buttonSize = ImVec2(childSize.x, 55);

    createButton(
        "login_button",
        "Sign in",
        buttonSize,
        [this] {
            presenter->onLoginButtonClicked();
        }
    );

    addVerticalSpacing();

    createButton(
        "signup_button",
        "Sign up",
        buttonSize,
        [this] {
            presenter->onSignUpButtonClicked();
        }
    );
}
