//
// Created by belyashik2k on 4/27/25.
//

#include <imgui.h>

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiColors.h"
#include "views/imgui/ImguiStyleColorGuard.h"
#include "views/imgui/ImguiStyleVarGuard.h"
#include "views/imgui/ImguiView.h"
#include "views/imgui/ImguiWindow.h"
#include "views/imgui/sign_in/ImguiSignInView.h"

void ImguiSignInView::render() {
    ImguiWindow window("Sign In Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); {
        ImguiUtils::updateBackground("../assets/textures/auth/background.jpg");
        renderLoginForm();
    }
}

void ImguiSignInView::renderLoginForm() const {
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float childWidth = windowSize.x * 0.33f;
    const float childHeight = windowSize.y * 0.43f;
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
    ImguiUtils::printText(headerText, BLACK, 30, true);
    ImguiUtils::addVerticalSpacing(6);
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
    const auto &inputSize = ImVec2(childSize.x, 18);

    ImguiUtils::printText("Username", BLACK, 23, false);
    ImguiUtils::addVerticalSpacing();
    if (const auto &sp = presenter.lock() ) {
        ImguiUtils::createInputField(
            "username_input",
            "Username",
            sp->getUsername(),
            sp->getBufferSize(),
            inputSize,
            ImGuiInputTextFlags_CharsNoBlank,
            false
        );
        ImguiUtils::addVerticalSpacing();
        ImguiUtils::printText("Password", BLACK, 23, false);
        ImguiUtils::createInputField(
            "password_input",
            "Password",
            sp->getPassword(),
            sp->getBufferSize(),
            inputSize,
            ImGuiInputTextFlags_Password,
            false
        );
    }
    ImguiUtils::addVerticalSpacing(6);
}

void ImguiSignInView::renderFormButtons() const {
    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const ImVec2 childSize = ImGui::GetWindowSize();
    const auto &buttonSize = ImVec2(childSize.x, 60);

    {
        ImguiStyleColorGuard signInButton({
            {ImGuiCol_Text, WHITE},
            {ImGuiCol_Border, WHITE},
            {ImGuiCol_Button, GRAY},
        });
        ImguiUtils::createButton(
            "login_button",
            "Sign in",
            buttonSize,
            [this] {
                if (const auto &sp = presenter.lock()) {
                    sp->onLoginButtonClicked();
                }
            }
        );
    }

    ImguiUtils::addVerticalSpacing();

    {
        ImguiStyleColorGuard signUpButton({
            {ImGuiCol_Text, BLACK},
            {ImGuiCol_Border, BLACK},
            {ImGuiCol_Button, WHITE},
        });
        ImguiUtils::createButton(
            "signup_button",
            "Don't have an account? Sign up",
            buttonSize,
            [this] {
                if (const auto &sp = presenter.lock()) {
                    sp->onSignUpButtonClicked();
                }
            }
        );
    }
}

void ImguiSignInView::renderLoginError() const {
    if (const auto &sp = presenter.lock()) {
        if (sp->isIncorrectLogin()) {
            ImguiUtils::addVerticalSpacing(3);
            ImguiUtils::printText("Invalid username or password", RED, 22, true);
        }
    }
}
