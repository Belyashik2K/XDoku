//
// Created by belyashik2k on 8/27/26.
//

#ifndef ENVCONFIG_H
#define ENVCONFIG_H

#include <string>

// Minimal .env support: reads KEY=VALUE pairs from a .env file into the process
// environment (without overriding variables the environment already has), and
// provides a getenv-with-default helper. Kept dependency-free on purpose so the
// project doesn't need a third-party dotenv library just for local dev config.
namespace EnvConfig {
    // Loads exactly the given file, if it exists. No-op otherwise.
    void loadDotEnv(const std::string &path);

    // Tries the common locations for .env relative to the working directory
    // the binary is launched from: "./.env" (running from the project root)
    // and "../.env" (running from a build directory one level below the
    // project root, e.g. `cd build && ./XDoku`, which is also how assets are
    // located - see the "../assets/..." paths throughout the views).
    void loadDotEnv();

    std::string getOrDefault(const std::string &key, const std::string &defaultValue);
}

#endif //ENVCONFIG_H
