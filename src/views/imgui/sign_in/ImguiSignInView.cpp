//
// Created by belyashik2k on 4/27/25.
//

#include "views/imgui/sign_in/ImguiSignInView.h"

#include <imgui.h>

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiColors.h"
#include "views/imgui/ImguiStyleColorGuard.h"
#include "views/imgui/ImguiStyleVarGuard.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSignInView::render() {
    ImguiWindow window("Sign In Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); {
        updateBackground("../assets/textures/auth/background.jpg");
        renderLoginForm();
    }
}

void ImguiSignInView::renderLoginForm() const {
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
    renderLoginError();
}

void ImguiSignInView::renderFormHeader() {
    const auto headerText = "Sign in to XDoku";
    printText(headerText, BLACK, 28, true);
    addVerticalSpacing(6);
}

void ImguiSignInView::renderFormInputs() const {
    ImguiStyleColorGuard localColorGuard({
        {ImGuiCol_Text, WHITE},
        {ImGuiCol_Border, LIGHT_GRAY},
        {ImGuiCol_FrameBg, GRAY},
    });

    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const ImVec2 childSize = ImGui::GetWindowSize();
    const auto &inputSize = ImVec2(childSize.x, 15);

    printText("Username", BLACK, 20, false);
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
    printText("Password", BLACK, 20, false);
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
            {ImGuiCol_Text, WHITE},
            {ImGuiCol_Border, WHITE},
            {ImGuiCol_Button, GRAY},
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
            {ImGuiCol_Text, BLACK},
            {ImGuiCol_Border, BLACK},
            {ImGuiCol_Button, WHITE},
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

void ImguiSignInView::renderLoginError() const {
    if (presenter->isIncorrectLogin()) {
        ImguiStyleColorGuard localColorGuard({
            {ImGuiCol_Text, RED},
            {ImGuiCol_Border, LIGHT_GRAY},
            {ImGuiCol_FrameBg, GRAY},
        });

        ImguiStyleVarGuard localVarGuard({
            {ImGuiStyleVar_FrameRounding, 10.0f},
            {ImGuiStyleVar_FrameBorderSize, 1.0f}
        });

        addVerticalSpacing(3);
        printText("Invalid username or password", RED, 22, true);
    }
}
