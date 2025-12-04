//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUITEXTUREMANAGER_H
#define IMGUITEXTUREMANAGER_H

#include <string>
#include <unordered_map>
#include <GLFW/glfw3.h>

struct TextureData {
    GLuint textureID = 0;
    int width = 0;
    int height = 0;
};

class ImguiTextureManager {
public:
    static ImguiTextureManager &getInstance() {
        static ImguiTextureManager instance;
        return instance;
    }

    GLuint loadTextureFromFile(const std::string &filePath);

    void cleanup();

private:
    ImguiTextureManager() = default;
    ~ImguiTextureManager() {
        cleanup();
    }

    static bool memoryTextureLoader(
        const void *data,
        size_t data_size,
        GLuint *out_texture,
        int *out_width,
        int *out_height
    );
    static bool fileTextureLoader(const char *file_name, GLuint *out_texture, int *out_width, int *out_height);

    std::unordered_map<std::string, TextureData> textureCache = {};
};

#endif //IMGUITEXTUREMANAGER_H
