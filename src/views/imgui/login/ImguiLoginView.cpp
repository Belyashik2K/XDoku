//
// Created by belyashik2k on 4/27/25.
//

#include "views/imgui/login/ImguiLoginView.h"

#include <iostream>
#include <glad/glad.h>
#include <imgui.h>

#include "managers/TextureManager.h"
#include "views/imgui/ImguiChildWindow.h"
#include "views/imgui/ImguiWindow.h"

void ImguiLoginView::render() {
    ImguiWindow window("Login Menu", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
    updateBackground("../assets/textures/background.jpg");

    constexpr int childWidth = 650;
    constexpr int childHeight = 350;
    constexpr ImVec2 childSize(childWidth, childHeight);

    const ImVec2 windowSize = ImGui::GetWindowSize();
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

    float textWidth = ImGui::CalcTextSize("Sign in to XDoku").x;
    ImGui::SetCursorPosX((childWidth - textWidth) * 0.5f);
    ImGui::Text("Sign in to XDoku");
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::PushItemWidth(childWidth);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(15.0f, 15.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

    ImGui::InputText("##Username", presenter->getUsername(), presenter->getBufferSize(), ImGuiInputTextFlags_CharsNoBlank);
    ImGui::Spacing();
    ImGui::InputText("##Password", presenter->getPassword(), presenter->getBufferSize(), ImGuiInputTextFlags_Password);
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::PopItemWidth();

    const auto &buttonSize = ImVec2(childWidth, 55);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    ImGui::PushID("login_button");
    ImGui::Button("Sign in", buttonSize);
    ImGui::PopID();
    ImGui::Spacing();
    if (ImGui::IsItemClicked(0)) {
        presenter->onLoginButtonClicked();
    }

    ImGui::PushID("exit_button");
    ImGui::Button("Sign up", buttonSize);
    ImGui::PopID();
    if (ImGui::IsItemClicked(0)) {
        presenter->onSignUpButtonClicked();
    }

    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(3);
}
