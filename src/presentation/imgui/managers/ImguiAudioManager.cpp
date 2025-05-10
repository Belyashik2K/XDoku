//
// Created by belyashik2k on 5/10/25.
//

#define MINIAUDIO_IMPLEMENTATION
#include "presentation/imgui/managers/ImguiAudioManager.h"

#include <iostream>
#include <ostream>

bool ImguiAudioManager::init() {
    if (ma_engine_init(nullptr, &engine_) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine" << std::endl;
        return false;
    }
    return true;
}

void ImguiAudioManager::shutdown() {
    for (auto &pair : sounds_) {
        ma_sound_uninit(pair.second);
        delete pair.second;
    }
    sounds_.clear();
    ma_engine_uninit(&engine_);
}

void ImguiAudioManager::loadAudio(const std::string &path) {
    auto *sound = new ma_sound;
    if (ma_sound_init_from_file(&engine_, path.c_str(), MA_SOUND_FLAG_DECODE, nullptr, nullptr, sound) != MA_SUCCESS) {
        std::cerr << "Failed to load audio file: " << path << std::endl;
        delete sound;
        return;
    }
    sounds_[path] = sound;
}

void ImguiAudioManager::playAudio(const std::string &path) {
    if (auto it = sounds_.find(path); it != sounds_.end()) {
        if (ma_sound *sound = it->second; ma_sound_start(sound) != MA_SUCCESS) {
            std::cerr << "Failed to play audio: " << path << std::endl;
        }
    } else {
        std::cerr << "Audio not loaded: " << path << std::endl;
    }
};

