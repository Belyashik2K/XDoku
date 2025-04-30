//
// Created by belyashik2k on 4/30/25.
//

#ifndef IMGUISTYLEVARGUARD_H
#define IMGUISTYLEVARGUARD_H
#include <imgui.h>
#include <vector>

class ImguiStyleGuard {
public:
    // explicit ImguiStyleGuard(const std::vector<std::pair<ImGuiStyleVar, ImVec2>>& styles);
    // explicit ImguiStyleGuard(const std::vector<std::pair<ImGuiStyleVar, float>>& styles);

    template<typename T>
    explicit ImguiStyleGuard(const std::vector<std::pair<ImGuiStyleVar, T>>& styles) {
        for (const auto& [var, value] : styles) {
            ImGui::PushStyleVar(var, value);
            count++;
        }
    }

    ~ImguiStyleGuard() {
        ImGui::PopStyleVar(count);
    }

private:
    int count = 0;
};

#endif //IMGUISTYLEVARGUARD_H
