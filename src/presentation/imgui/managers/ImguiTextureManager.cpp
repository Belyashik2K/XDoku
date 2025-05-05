//
// Created by belyashik2k on 4/29/25.
//

#include "presentation/imgui/managers/ImguiTextureManager.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <imgui.h>
#include <stb_image.h>

bool ImguiTextureManager::memoryTextureLoader(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height)
{
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

bool ImguiTextureManager::fileTextureLoader(const char* file_name, GLuint* out_texture, int* out_width, int* out_height)
{
    FILE* f = fopen(file_name, "rb");
    if (f == NULL)
        return false;
    fseek(f, 0, SEEK_END);
    const size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
        return false;
    fseek(f, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);
    const bool ret = memoryTextureLoader(file_data, file_size, out_texture, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}

GLuint ImguiTextureManager::loadTextureFromFile(const std::string &filePath) {
    if (textureCache.contains(filePath)) {
        return textureCache[filePath].textureID;
    }

    TextureData data;

    if (const bool success = fileTextureLoader(filePath.c_str(), &data.textureID, &data.width, &data.height); !success) {
        throw std::runtime_error("[TextureManager] Failed to load texture from file: " + filePath);
    }

    textureCache[filePath] = data;
    return data.textureID;
}

void ImguiTextureManager::cleanup() {
    for (const auto &pair : textureCache) {
        glDeleteTextures(1, &pair.second.textureID);
    }
    textureCache.clear();
}
