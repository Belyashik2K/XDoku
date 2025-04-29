//
// Created by belyashik2k on 4/29/25.
//

#include "views/imgui/sign_up/ImguiSignUpView.h"

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSignUpView::render() {
    ImguiWindow window("Sign up Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
    updateBackground("../assets/textures/background.jpg");

    {
        const ImVec2 windowSize = ImGui::GetWindowSize();
        const float childWidth = windowSize.x / 3;
        const float childHeight = 450.0f;
        const ImVec2 childSize(childWidth, childHeight);

        ImVec2 childPosition;
        childPosition.x = (windowSize.x - childSize.x) * 0.5f;
        childPosition.y = (windowSize.y - childSize.y) * 0.5f;

        ImGui::SetCursorPos(childPosition);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

        ImguiChildWindow childWindow(
            "CenteredChild",
            childSize,
            ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize
        );

        ImGui::PopStyleVar();

        const float textWidth = ImGui::CalcTextSize("Sign in to XDoku").x;
        ImGui::SetCursorPosX((childWidth - textWidth) * 0.5f);
        ImGui::Text("Sign up to XDoku");
        addVerticalSpacing(6);

        ImGui::PushItemWidth(childWidth);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15.0f, 15.0f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

        ImGui::InputText("##Username", presenter->getUsername(), presenter->getBufferSize(),
                         ImGuiInputTextFlags_CharsNoBlank);
        addVerticalSpacing();
        ImGui::InputText("##Email", presenter->getEmail(), presenter->getBufferSize(),
                         ImGuiInputTextFlags_CharsNoBlank);
        addVerticalSpacing();
        ImGui::InputText("##Password", presenter->getPassword(), presenter->getBufferSize(),
                         ImGuiInputTextFlags_Password);
        addVerticalSpacing();
        ImGui::InputText("##RepeatPassword", presenter->getConfirmPassword(), presenter->getBufferSize(),
                         ImGuiInputTextFlags_Password);
        addVerticalSpacing(6);
        ImGui::PopItemWidth();


        const auto &buttonSize = ImVec2(childWidth, 55);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

        createButton("signup_button", "Sign up", buttonSize,
                     [this] {
                         presenter->onSignUpButtonClicked();
                     }
        );
        addVerticalSpacing();
        createButton("sign_in_button", "Back to sign in", buttonSize,
                     [this] {
                         presenter->onBackButtonClicked();
                     }
        );

        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(3);
    }
}
