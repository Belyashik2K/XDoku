//
// Created by Belyashik2K on 02.05.2025.
//

#ifndef IMGUIFONTMANAGER_H
#define IMGUIFONTMANAGER_H

#include "imgui.h"
#include <unordered_map>
#include <string>

class ImguiFontManager {
public:
    static ImguiFontManager& getInstance() {
        static ImguiFontManager instance;
        return instance;
    }

    void setFontPath(const std::string &path);
    ImFont* getFont(int size);

private:
    ImguiFontManager() = default;

    std::string fontPath = "";
    std::unordered_map<int, ImFont*> fonts = {};
};


#endif //IMGUIFONTMANAGER_H
