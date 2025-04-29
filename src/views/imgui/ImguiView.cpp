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
}
