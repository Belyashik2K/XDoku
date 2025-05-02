//
// Created by belyashik2k on 4/29/25.
//

#include "views/imgui/sign_up/ImguiSignUpView.h"

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiColors.h"
#include "views/imgui/ImguiStyleColorGuard.h"
#include "views/imgui/ImguiStyleVarGuard.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSignUpView::render() {
    ImguiWindow window("Sign Up Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove); {
        updateBackground("../assets/textures/auth/background.jpg");
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
    printText(headerText, BLACK, 30, true);
    addVerticalSpacing(6);
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

    printText("Username", BLACK, 23, false);
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
    printText("Email", BLACK, 23, false);
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
    printText("Password", BLACK, 23, false);
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
    printText("Repeat Password", BLACK, 23, false);
    createInputField(
        "repeat_password_input",
        "Repeat password",
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

    const auto &buttonSize = ImVec2(ImGui::GetWindowSize().x, 60);

    {
        ImguiStyleColorGuard signUpButton({
            {ImGuiCol_Text, WHITE},
            {ImGuiCol_Border, WHITE},
            {ImGuiCol_Button, GRAY},
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

    addVerticalSpacing();

    {
        ImguiStyleColorGuard backToSingInButton({
            {ImGuiCol_Text, BLACK},
            {ImGuiCol_Border, BLACK},
            {ImGuiCol_Button, WHITE},
        });
        createButton(
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
        addVerticalSpacing(3);
        printText(presenter->getErrorMessage().c_str(), RED, 23, true);
    }
}