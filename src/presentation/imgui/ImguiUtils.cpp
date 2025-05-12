//
// Created by belyashik2k on 4/29/25.
//

#include <GLFW/glfw3.h>

#include <presentation/imgui/ImguiUtils.h>
#include <presentation/imgui/managers/ImguiTextureManager.h>
#include <presentation/imgui/guards/ImguiStyleColorGuard.h>
#include "presentation/imgui/managers/ImguiFontManager.h"

void ImguiUtils::updateBackground(const std::string &filePath) {
    const GLuint backgroundTex = ImguiTextureManager::getInstance().loadTextureFromFile(filePath);
    const ImVec2 windowPos = ImGui::GetWindowPos();
    const ImVec2 windowSize = ImGui::GetWindowSize();
    ImDrawList *drawList = ImGui::GetWindowDrawList();

    drawList->AddImage(
        backgroundTex,
        windowPos,
        ImVec2(windowPos.x + windowSize.x,
               windowPos.y + windowSize.y),
        ImVec2(0, 0),
        ImVec2(1, 1),
        IM_COL32(255, 255, 255, 255)
    );
}

void ImguiUtils::createButton(
    const char *id,
    const char *label,
    const ImVec2 &size,
    const std::function<void()> &onLeftClick,
    const std::function<void()> &onRightClick,
    const bool isCentered
) {
    if (isCentered) {
        centerCursor(size);
    }

    ImGui::PushID(id);
    ImGui::Button(label, size);
    ImGui::PopID();
    if (ImGui::IsItemClicked(0)) {
        if (onLeftClick) {
            onLeftClick();
        }
    }
    if (ImGui::IsItemClicked(1)) {
        if (onRightClick) {
            onRightClick();
        }
    }
}

void ImguiUtils::addVerticalSpacing(const int count) {
    for (int i = 0; i < count; ++i) {
        ImGui::Spacing();
    }
}

void ImguiUtils::printText(
    const char *text,
    const ImColor &color,
    const int fontSize,
    const bool isCentered
) {
    ImguiStyleColorGuard localColorGuard({
        {ImGuiCol_Text, color},
    });
    ImGui::PushFont(ImguiFontManager::getInstance().getFont(fontSize));

    if (isCentered) {
        const ImVec2 textWidth = ImGui::CalcTextSize(text);
        centerCursor(textWidth);
    }
    ImGui::Text(text);

    ImGui::PopFont();
}

void ImguiUtils::centerCursor(const ImVec2 &sizeOfObject) {
    const float width = ImGui::GetWindowSize().x;
    ImGui::SetCursorPosX((width - sizeOfObject.x) * 0.5f);
}

void ImguiUtils::createInputField(
    const char *id,
    const char *label,
    char *buffer,
    const int bufferSize,
    const ImVec2 &size,
    const ImGuiInputTextFlags flags,
    const bool isLabelHidden
) {
    ImGui::PushID(id);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, size.y));
    ImGui::PushItemWidth(size.x);

    auto resultLabel = std::string(label);
    if (isLabelHidden) {
        resultLabel = "##" + resultLabel;
    }

    ImGui::InputText(resultLabel.c_str(), buffer, bufferSize, flags);

    ImGui::PopItemWidth();
    ImGui::PopStyleVar();
    ImGui::PopID();
}
