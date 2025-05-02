//
// Created by belyashik2k on 4/29/25.
//

#include "views/imgui/sign_up/ImguiSignUpView.h"

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiStyleColorGuard.h"
#include "views/imgui/ImguiStyleVarGuard.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSignUpView::render() {
    ImguiWindow window("Sign Up Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); {
        updateBackground("../assets/textures/background.jpg");
        renderSignUpForm();
    }
}

void ImguiSignUpView::renderSignUpForm() const {
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float childWidth = windowSize.x * 0.33f;
    const float childHeight = windowSize.y * 0.55f;
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

void ImguiSignUpView::renderFormHeader() {
    const auto headerText = "Sign up to XDoku";
    printText(headerText, ImColor(0, 0, 0), 28, true);
    addVerticalSpacing(6);
}

void ImguiSignUpView::renderFormInputs() const {
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
    printText("Email", ImColor(0, 0, 0), 20, false);
    createInputField(
        "email_input",
        "Email",
        presenter->getEmail(),
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
    addVerticalSpacing();
    printText("Repeat Password", ImColor(0, 0, 0), 20, false);
    createInputField(
        "repeat_password_input",
        "Repeat Password",
        presenter->getConfirmPassword(),
        presenter->getBufferSize(),
        inputSize,
        ImGuiInputTextFlags_Password,
        false
    );
    addVerticalSpacing(6);
}

void ImguiSignUpView::renderFormButtons() const {
    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const auto &buttonSize = ImVec2(ImGui::GetWindowSize().x, 55);

    {
        ImguiStyleColorGuard signUpButton({
            {ImGuiCol_Text, ImColor(255, 255, 255)},
            {ImGuiCol_Border, ImColor(255, 255, 255)},
        });
        createButton("signup_button", "Sign up", buttonSize,
                 [this] {
                     presenter->onSignUpButtonClicked();
                 }
        );
    }

    addVerticalSpacing();

    {
        ImguiStyleColorGuard backToSingInButton({
            {ImGuiCol_Text, ImColor(0, 0, 0)},
            {ImGuiCol_Border, ImColor(0, 0, 0)},
            {ImGuiCol_Button, ImColor(255, 255, 255)},
        });
        createButton("sign_in_button", "Back to sign in", buttonSize,
                     [this] {
                         presenter->onBackButtonClicked();
                     }
        );
    }
}