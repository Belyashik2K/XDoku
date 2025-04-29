//
// Created by belyashik2k on 4/5/25.
//

#ifndef UTILS_H
#define UTILS_H
#include <optional>
#include <string>
#include <GLFW/glfw3.h>

std::optional<std::string> getDeviceHWID();
bool LoadTextureFromMemory(const void* data, size_t data_size, GLuint* out_texture, int* out_width, int* out_height);
bool LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height);

#endif //UTILS_H
