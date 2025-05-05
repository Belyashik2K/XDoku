//
// Created by Belyashik2K on 02.05.2025.
//

#include <presentation/imgui/managers/ImguiFontManager.h>
#include <stdexcept>

void ImguiFontManager::setFontPath(const std::string &path) {
    fontPath = path;
}

ImFont* ImguiFontManager::getFont(const int size) {
    if (const auto it = fonts.find(size); it != fonts.end()) {
        return it->second;
    }

    const ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), size);
    if (font) {
        fonts[size] = font;
        io.Fonts->Build();
        return font;
    }
    printf("[FontManager] Failed to load font from %s\n", fontPath.c_str());
    throw std::runtime_error("[FontManager] Failed to load font");
}

