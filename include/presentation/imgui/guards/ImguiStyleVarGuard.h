//
// Created by belyashik2k on 4/30/25.
//

#ifndef IMGUISTYLEVARGUARD_H
#define IMGUISTYLEVARGUARD_H

#include <imgui.h>
#include <variant>
#include <vector>

class ImguiStyleVarGuard {
public:
    using AvailableTypes = std::variant<ImVec2, float>;

    explicit ImguiStyleVarGuard(const std::vector<std::pair<ImGuiStyleVar, AvailableTypes>> &styles);
    ~ImguiStyleVarGuard();

private:
    int count = 0;
};

#endif //IMGUISTYLEVARGUARD_H
