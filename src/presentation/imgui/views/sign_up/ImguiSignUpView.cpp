//
// Created by belyashik2k on 4/29/25.
//

#include "application/presenters/SignUpPresenter.h"
#include "presentation/imgui/views/sign_up/ImguiSignUpView.h"
#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiChildWindowGuard.h"
#include "presentation/imgui/guards/ImguiStyleColorGuard.h"
#include "presentation/imgui/guards/ImguiStyleVarGuard.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiSignUpView::render() {
    ImguiWindowGuard window("Sign Up Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); {
        ImguiUtils::updateBackground("../assets/textures/auth/background.jpg");
        renderSignUpForm();
    }
}

void ImguiSignUpView::renderSignUpForm() const {
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float childWidth = windowSize.x * 0.33f;
    const float childHeight = windowSize.y * 0.60f;
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
    renderSignUpError();
}

void ImguiSignUpView::renderFormHeader() {
    const auto headerText = "Sign up to XDoku";
    ImguiUtils::printText(headerText, BLACK, 30, true);
    ImguiUtils::addVerticalSpacing(6);
}

void ImguiSignUpView::renderFormInputs() const {
    ImguiStyleColorGuard localColorGuard({
        {ImGuiCol_Text, WHITE},
        {ImGuiCol_Border, WHITE},
        {ImGuiCol_FrameBg, GRAY},
    });

    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const ImVec2 childSize = ImGui::GetWindowSize();
    const auto &inputSize = ImVec2(childSize.x, 18);

    ImguiUtils::printText("Username", BLACK, 23, false);

    ImguiUtils::createInputField(
        "username_input",
        "Username",
        presenter->getUsername(),
        presenter->getBufferSize(),
        inputSize,
        ImGuiInputTextFlags_CharsNoBlank,
        false
    );
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText("Email", BLACK, 23, false);
    ImguiUtils::createInputField(
        "email_input",
        "Email",
        presenter->getEmail(),
        presenter->getBufferSize(),
        inputSize,
        ImGuiInputTextFlags_CharsNoBlank,
        false
    );
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText("Password", BLACK, 23, false);
    ImguiUtils::createInputField(
        "password_input",
        "Password",
        presenter->getPassword(),
        presenter->getBufferSize(),
        inputSize,
        ImGuiInputTextFlags_Password,
        false
    );
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText("Repeat Password", BLACK, 23, false);
    ImguiUtils::createInputField(
        "repeat_password_input",
        "Repeat password",
        presenter->getConfirmPassword(),
        presenter->getBufferSize(),
        inputSize,
        ImGuiInputTextFlags_Password,
        false
    );

    ImguiUtils::addVerticalSpacing(6);
}

void ImguiSignUpView::renderFormButtons() const {
    ImguiStyleVarGuard localVarGuard({
        {ImGuiStyleVar_FrameRounding, 10.0f},
        {ImGuiStyleVar_FrameBorderSize, 1.0f}
    });

    const auto &buttonSize = ImVec2(ImGui::GetWindowSize().x, 60);

    {
        ImguiStyleColorGuard signUpButton({
            {ImGuiCol_Text, WHITE},
            {ImGuiCol_Border, WHITE},
            {ImGuiCol_Button, GRAY},
        });
        ImguiUtils::createButton(
            "signup_button",
            "Sign up",
            buttonSize,
            [this] {
                presenter->onSignUpButtonClicked();
            }
        );
    }

    ImguiUtils::addVerticalSpacing();

    {
        ImguiStyleColorGuard backToSingInButton({
            {ImGuiCol_Text, BLACK},
            {ImGuiCol_Border, BLACK},
            {ImGuiCol_Button, WHITE},
        });
        ImguiUtils::createButton(
            "sign_in_button",
            "Back to sign in",
            buttonSize,
            [this] {
                presenter->onBackButtonClicked();
            }
        );
    }
}

void ImguiSignUpView::renderSignUpError() const {
    if (const std::string errorMessage = presenter->getErrorMessage(); !errorMessage.empty()) {
        ImguiUtils::addVerticalSpacing(3);
        ImguiUtils::printText(presenter->getErrorMessage().c_str(), RED, 23, true);
    }
}