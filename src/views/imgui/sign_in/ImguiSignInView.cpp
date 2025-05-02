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
    const float childWidth = windowSize.x * 0.33f;
    const float childHeight = windowSize.y * 0.4f;
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
    printText(headerText, ImColor(0, 0, 0), 28, true);
    addVerticalSpacing(6);
}

void ImguiSignInView::renderFormInputs() const {
    ImguiStyleColorGuard localColorGuard({
        {ImGuiCol_Text, ImColor(255, 255, 255)},
        {ImGuiCol_Border, ImColor(255, 255, 255)},
        {ImGuiCol_FrameBg, ImColor(35, 35, 36)},
    });

    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const ImVec2 childSize = ImGui::GetWindowSize();
    const auto &inputSize = ImVec2(childSize.x, 15);

    printText("Username", ImColor(0, 0, 0), 20, false);
    addVerticalSpacing();
    createInputField(
        "username_input",
        "Username",
        presenter->getUsername(),
        presenter->getBufferSize(),
        inputSize,
        ImGuiInputTextFlags_CharsNoBlank,
        false
    );
    addVerticalSpacing();
    printText("Password", ImColor(0, 0, 0), 20, false);
    createInputField(
        "password_input",
        "Password",
        presenter->getPassword(),
        presenter->getBufferSize(),
        inputSize,
        ImGuiInputTextFlags_Password,
        false
    );
    addVerticalSpacing(6);
}

void ImguiSignInView::renderFormButtons() const {
    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const ImVec2 childSize = ImGui::GetWindowSize();
    const auto &buttonSize = ImVec2(childSize.x, 55);

    {
        ImguiStyleColorGuard signInButton({
            {ImGuiCol_Text, ImColor(255, 255, 255)},
            {ImGuiCol_Border, ImColor(255, 255, 255)},
        });
        createButton(
            "login_button",
            "Sign in",
            buttonSize,
            [this] {
                presenter->onLoginButtonClicked();
            }
        );
    }

    addVerticalSpacing();

    {
        ImguiStyleColorGuard signUpButton({
            {ImGuiCol_Text, ImColor(0, 0, 0)},
            {ImGuiCol_Border, ImColor(0, 0, 0)},
            {ImGuiCol_Button, ImColor(255, 255, 255)},
        });
        createButton(
            "signup_button",
            "Sign up",
            buttonSize,
            [this] {
                presenter->onSignUpButtonClicked();
            }
        );
    }
}
