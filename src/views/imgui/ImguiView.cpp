//
// Created by belyashik2k on 4/29/25.
//

#include "views/imgui/ImguiView.h"

#include <imgui.h>

#include "managers/TextureManager.h"

void IImguiView::updateBackground(const std::string &filePath) {
    const GLuint backgroundTex = TextureManager::GetInstance().loadTextureFromFile(filePath);
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

void IImguiView::createButton(
    const char *id,
    const char *label,
    const ImVec2 &size,
    const std::function<void()> &onLeftClick,
    const std::function<void()> &onRightClick
) {
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

void IImguiView::addVerticalSpacing(const int count) {
    for (int i = 0; i < count; ++i) {
        ImGui::Spacing();
    }
}

void IImguiView::printText(const char *text, const bool isCentered) {
    if (isCentered) {
        const ImVec2 textWidth = ImGui::CalcTextSize(text);
        centerCursor(textWidth);
    }
    ImGui::Text(text);
}

void IImguiView::centerCursor(const ImVec2 &sizeOfObject) {
    const float width = ImGui::GetWindowSize().x;
    ImGui::SetCursorPosX((width - sizeOfObject.x) * 0.5f);
}

void IImguiView::createInputField(
    const char *id,
    const char *label,
    char *buffer,
    const int bufferSize,
    const ImGuiInputTextFlags flags,
    const bool isLabelHidden
) {
    ImGui::PushID(id);

    auto resultLabel = std::string(label);
    if (isLabelHidden) {
        resultLabel = "##" + resultLabel;
    }

    ImGui::InputText(resultLabel.c_str(), buffer, bufferSize, flags);

    ImGui::PopID();
}
