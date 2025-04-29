//
// Created by belyashik2k on 4/27/25.
//

#include "views/imgui/login/ImguiLoginView.h"

#include <iostream>
#include <glad/glad.h>
#include <imgui.h>

#include "managers/TextureManager.h"

void ImguiLoginView::render() {
    const GLuint backgroundTex = TextureManager::GetInstance().loadTextureFromFile("../assets/textures/background.jpg");

    char *username = presenter->getUsername();
    char *password = presenter->getPassword();

    ImGui::Begin(
        "Login Menu",
        nullptr,
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove
    );

    const ImVec2 windowPos = ImGui::GetWindowPos();
    const ImVec2 windowSize = ImGui::GetWindowSize();
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    drawList->AddImage(
        backgroundTex,
        windowPos,
        ImVec2(windowPos.x + windowSize.x,
               windowPos.y + windowSize.y),
        ImVec2(0, 0),
        ImVec2(1, 1),
        IM_COL32(255, 255, 255, 255)
    );

    constexpr int childWidth = 650;
    constexpr int childHeight = 350;
    constexpr ImVec2 childSize(childWidth, childHeight);

    ImVec2 childPosition;
    childPosition.x = (windowSize.x - childSize.x) * 0.5f;
    childPosition.y = (windowSize.y - childSize.y) * 0.5f;

    ImGui::SetCursorPos(childPosition);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::BeginChild("CenteredChild", childSize, ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize);
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

    ImGui::InputText("##Username", username, 128, ImGuiInputTextFlags_CharsNoBlank);
    ImGui::Spacing();
    ImGui::InputText("##Password", password, 128, ImGuiInputTextFlags_Password);
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

    ImGui::EndChild();
}
