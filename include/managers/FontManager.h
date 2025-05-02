//
// Created by Belyashik2K on 02.05.2025.
//

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "imgui.h"
#include <unordered_map>
#include <string>

class FontManager {
public:
    static FontManager& getInstance() {
        static FontManager instance;
        return instance;
    }

    void setFontPath(const std::string &path);
    ImFont* getFont(int size);

private:
    FontManager() = default;

    std::string fontPath = "";
    std::unordered_map<int, ImFont*> fonts = {};
};


#endif //FONTMANAGER_H
