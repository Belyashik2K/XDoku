//
// Created by belyashik2k on 4/27/25.
//

#include <imgui.h>

#include "application/presenters/SignInPresenter.h"
#include "presentation/imgui/views/sign_in/ImguiSignInView.h"
#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiChildWindowGuard.h"
#include "presentation/imgui/guards/ImguiStyleColorGuard.h"
#include "presentation/imgui/guards/ImguiStyleVarGuard.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiSignInView::render() {
    ImguiWindowGuard window("Sign In Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); {
        ImguiUtils::updateBackground("../assets/textures/auth/background.jpg");
        renderLoginForm();
    }
}

void ImguiSignInView::renderLoginForm() const {
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float childWidth = windowSize.x * 0.33f;
    const float childHeight = windowSize.y * 0.43f;
    const ImVec2 childSize(childWidth, childHeight);

    ImguiChildWindowGuard childWindow(
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
    const auto sp = getPresenter();
    if (!sp) return;

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
    ImguiUtils::addVerticalSpacing(6);
}

void ImguiSignInView::renderFormButtons() const {
    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const ImVec2 childSize = ImGui::GetWindowSize();
    const auto &buttonSize = ImVec2(childSize.x, 60); {
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
                const auto sp = getPresenter();
                if (!sp) return;
                sp->onLoginButtonClicked();
            }
        );
    }

    ImguiUtils::addVerticalSpacing(); {
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
                const auto sp = getPresenter();
                if (!sp) return;
                sp->onSignUpButtonClicked();
            }
        );
    }
}

void ImguiSignInView::renderLoginError() const {
    const auto sp = getPresenter();
    if (!sp) return;

    const std::string errorMessage = sp->getErrorMessage();

    if (!errorMessage.empty()) {
        ImguiUtils::addVerticalSpacing(3);
        ImguiUtils::printText(errorMessage.c_str(), RED, 22, true);
    }
}
