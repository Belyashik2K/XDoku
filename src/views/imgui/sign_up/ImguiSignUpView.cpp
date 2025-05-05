//
// Created by belyashik2k on 4/29/25.
//

#include "views/imgui/sign_up/ImguiSignUpView.h"

#include "presenters/SignUpPresenter.h"
#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiColors.h"
#include "views/imgui/ImguiStyleColorGuard.h"
#include "views/imgui/ImguiStyleVarGuard.h"
#include "views/imgui/ImguiView.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSignUpView::render() {
    ImguiWindow window("Sign Up Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); {
        ImguiUtils::updateBackground("../assets/textures/auth/background.jpg");
        renderSignUpForm();
    }
}

void ImguiSignUpView::renderSignUpForm() const {
    const ImVec2 windowSize = ImGui::GetWindowSize();
    const float childWidth = windowSize.x * 0.33f;
    const float childHeight = windowSize.y * 0.60f;
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
    renderSignUpError();
}

void ImguiSignUpView::renderFormHeader() {
    const auto headerText = "Sign up to XDoku";
    ImguiUtils::printText(headerText, BLACK, 30, true);
    ImguiUtils::addVerticalSpacing(6);
}

void ImguiSignUpView::renderFormInputs() const {
    const auto sp = getPresenter();
    if (!sp) return;

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
        sp->getUsername(),
        sp->getBufferSize(),
        inputSize,
        ImGuiInputTextFlags_CharsNoBlank,
        false
    );
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText("Email", BLACK, 23, false);
    ImguiUtils::createInputField(
        "email_input",
        "Email",
        sp->getEmail(),
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
    ImguiUtils::addVerticalSpacing();
    ImguiUtils::printText("Repeat Password", BLACK, 23, false);
    ImguiUtils::createInputField(
        "repeat_password_input",
        "Repeat password",
        sp->getConfirmPassword(),
        sp->getBufferSize(),
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
                const auto sp = getPresenter();
                if (!sp) return;
                sp->onSignUpButtonClicked();
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
                const auto sp = getPresenter();
                if (!sp) return;
                sp->onBackButtonClicked();
            }
        );
    }
}

void ImguiSignUpView::renderSignUpError() const {
    const auto sp = getPresenter();
    if (!sp) return;

    if (const std::string errorMessage = sp->getErrorMessage(); !errorMessage.empty()) {
        ImguiUtils::addVerticalSpacing(3);
        ImguiUtils::printText(sp->getErrorMessage().c_str(), RED, 23, true);
    }
}