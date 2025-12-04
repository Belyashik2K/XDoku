//
// Created by belyashik2k on 5/10/25.
//

#ifndef IMGUIAUDIOMANAGER_H
#define IMGUIAUDIOMANAGER_H
#include <string>
#include <unordered_map>
#include <miniaudio.h>

class ImguiAudioManager {
public:
    static ImguiAudioManager &getInstance() {
        static ImguiAudioManager instance;
        return instance;
    }

    bool init();
    void shutdown();

    void loadAudio(const std::string &path);
    void playAudio(const std::string &path);

    void playInternal(const std::string &path);

    ImguiAudioManager(const ImguiAudioManager &) = delete;
    ImguiAudioManager &operator=(const ImguiAudioManager &) = delete;
private:
    ImguiAudioManager() = default;
    ~ImguiAudioManager() = default;

    ma_engine engine_;
    std::unordered_map<std::string, ma_sound*> sounds_;
};

#endif //IMGUIAUDIOMANAGER_H
