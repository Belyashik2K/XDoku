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
    void loadDotEnv(const std::string &path = ".env");

    std::string getOrDefault(const std::string &key, const std::string &defaultValue);
}

#endif //ENVCONFIG_H
