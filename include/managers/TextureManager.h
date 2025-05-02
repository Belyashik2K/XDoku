//
// Created by belyashik2k on 4/29/25.
//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <unordered_map>
#include <GLFW/glfw3.h>

struct TextureData {
    GLuint textureID = 0;
    int width = 0;
    int height = 0;
};

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    GLuint loadTextureFromFile(const std::string &filePath);

    void cleanup();

private:
    TextureManager() = default;
    ~TextureManager() = default;

    std::unordered_map<std::string, TextureData> textureCache = {};
};

#endif //TEXTUREMANAGER_H
