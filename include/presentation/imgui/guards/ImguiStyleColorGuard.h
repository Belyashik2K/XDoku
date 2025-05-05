//
// Created by Belyashik2K on 01.05.2025.
//

#ifndef IMGUISTYLECOLORGUARD_H
#define IMGUISTYLECOLORGUARD_H
#include <imgui.h>
#include <variant>
#include <vector>

class ImguiStyleColorGuard {
public:
    using AvailableTypes = std::variant<ImVec4, ImColor>;

    explicit ImguiStyleColorGuard(const std::vector<std::pair<ImGuiCol, AvailableTypes>> &styles);
    ~ImguiStyleColorGuard();

private:
    int count = 0;
};

#endif //IMGUISTYLECOLORGUARD_H
