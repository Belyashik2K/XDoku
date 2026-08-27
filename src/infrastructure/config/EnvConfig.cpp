#include "infrastructure/config/EnvConfig.h"

#include <cstdlib>
#include <fstream>
#include <sstream>

namespace {
    std::string trim(const std::string &value) {
        const auto start = value.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        const auto end = value.find_last_not_of(" \t\r\n");
        return value.substr(start, end - start + 1);
    }

    void setEnvIfMissing(const std::string &key, const std::string &value) {
#ifdef _WIN32
        if (std::getenv(key.c_str()) != nullptr) return;
        _putenv_s(key.c_str(), value.c_str());
#else
        setenv(key.c_str(), value.c_str(), 0);
#endif
    }
}

namespace EnvConfig {
    void loadDotEnv(const std::string &path) {
        std::ifstream file(path);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            const std::string trimmed = trim(line);
            if (trimmed.empty() || trimmed[0] == '#') continue;

            const auto separatorPos = trimmed.find('=');
            if (separatorPos == std::string::npos) continue;

            const std::string key = trim(trimmed.substr(0, separatorPos));
            std::string value = trim(trimmed.substr(separatorPos + 1));
            if (value.size() >= 2 && (value.front() == '"' || value.front() == '\'') &&
                value.back() == value.front()) {
                value = value.substr(1, value.size() - 2);
            }
            if (key.empty()) continue;

            setEnvIfMissing(key, value);
        }
    }

    void loadDotEnv() {
        loadDotEnv(".env");
        loadDotEnv("../.env");
    }

    std::string getOrDefault(const std::string &key, const std::string &defaultValue) {
        const char *value = std::getenv(key.c_str());
        return value ? std::string(value) : defaultValue;
    }
}
