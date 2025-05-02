//
// Created by belyashik2k on 4/29/25.
//

#include "managers/TextureManager.h"

#include <iostream>

#include "utils.h"

GLuint TextureManager::loadTextureFromFile(const std::string &filePath) {
    if (textureCache.contains(filePath)) {
        return textureCache[filePath].textureID;
    }

    TextureData data;

    if (const bool success = LoadTextureFromFile(filePath.c_str(), &data.textureID, &data.width, &data.height); !success) {
        throw std::runtime_error("[TextureManager] Failed to load texture from file: " + filePath);
    }

    textureCache[filePath] = data;
    return data.textureID;
}

void TextureManager::cleanup() {
    for (const auto &pair : textureCache) {
        glDeleteTextures(1, &pair.second.textureID);
    }
    textureCache.clear();
}
