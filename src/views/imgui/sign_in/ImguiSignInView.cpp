//
// Created by belyashik2k on 4/27/25.
//

#include "views/imgui/sign_in/ImguiSignInView.h"

#include <imgui.h>

#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiWindow.h"

void ImguiSignInView::render() {
    ImguiWindow window("Login Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
    {
        updateBackground("../assets/textures/background.jpg");

        {
            const ImVec2 windowSize = ImGui::GetWindowSize();
            const float childWidth = windowSize.x / 3;
            const float childHeight = windowSize.y / 3;
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
            ImGui::Text("Sign in to XDoku");
            addVerticalSpacing(6);

            ImGui::PushItemWidth(childWidth);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15.0f, 15.0f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

            ImGui::InputText("##Username", presenter->getUsername(), presenter->getBufferSize(), ImGuiInputTextFlags_CharsNoBlank);
            addVerticalSpacing();
            ImGui::InputText("##Password", presenter->getPassword(), presenter->getBufferSize(), ImGuiInputTextFlags_Password);
            addVerticalSpacing(6);
            ImGui::PopItemWidth();


            const auto &buttonSize = ImVec2(childWidth, 55);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

            createButton("login_button", "Sign in", buttonSize,
                [this] {
                    presenter->onLoginButtonClicked();
                }
            );
            addVerticalSpacing();

            createButton("signup_button", "Sign up", buttonSize,
                [this] {
                    presenter->onSignUpButtonClicked();
                }
            );

            ImGui::PopStyleColor(2);
            ImGui::PopStyleVar(3);
        }
    }

}
