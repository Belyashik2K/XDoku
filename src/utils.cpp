//
// Created by belyashik2k on 4/5/25.
//


#include <fstream>
#include <utils.h>

std::optional<std::string> getDeviceHWID() {
    // TODO: Implement a more secure way to get the HWID on different platforms
    std::ifstream file("/etc/machine-id");
    std::string hwid;
    if (file.is_open()) {
        std::getline(file, hwid);
        file.close();
    }

    if (hwid.empty()) {
        return std::nullopt;
    }
    return hwid;
}