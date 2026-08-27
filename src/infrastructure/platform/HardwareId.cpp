#include "infrastructure/platform/HardwareId.h"

#if defined(__linux__)
#include <array>
#include <fstream>
#elif defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

namespace {
    std::string trim(const std::string &value) {
        const auto start = value.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        const auto end = value.find_last_not_of(" \t\r\n");
        return value.substr(start, end - start + 1);
    }
}

namespace HardwareId {
#if defined(__linux__)
    // /etc/machine-id is systemd's stable per-installation ID. Some minimal
    // distros only ship the older dbus location, so fall back to that.
    std::optional<std::string> get() {
        for (const char *path: std::array{"/etc/machine-id", "/var/lib/dbus/machine-id"}) {
            std::ifstream file(path);
            if (!file.is_open()) continue;

            std::string id;
            std::getline(file, id);
            id = trim(id);
            if (!id.empty()) return id;
        }
        return std::nullopt;
    }
#elif defined(__APPLE__)
    // IOPlatformUUID is macOS's stable per-machine identifier, exposed on
    // the root of the IOKit registry.
    std::optional<std::string> get() {
        // kIOMainPortDefault (macOS 12+) replaced kIOMasterPortDefault, but
        // the old name is still what's available on older SDKs/deployment
        // targets - silence the deprecation warning rather than branching.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        const io_service_t platformExpert = IOServiceGetMatchingService(
            kIOMasterPortDefault, IOServiceMatching("IOPlatformExpertDevice")
        );
#pragma clang diagnostic pop
        if (!platformExpert) return std::nullopt;

        const CFTypeRef uuidProperty = IORegistryEntryCreateCFProperty(
            platformExpert, CFSTR("IOPlatformUUID"), kCFAllocatorDefault, 0
        );
        IOObjectRelease(platformExpert);
        if (!uuidProperty) return std::nullopt;

        std::optional<std::string> result;
        if (const auto uuidString = static_cast<CFStringRef>(uuidProperty)) {
            char buffer[64];
            if (CFStringGetCString(uuidString, buffer, sizeof(buffer), kCFStringEncodingUTF8)) {
                std::string id = trim(buffer);
                if (!id.empty()) result = id;
            }
        }
        CFRelease(uuidProperty);
        return result;
    }
#elif defined(_WIN32)
    // MachineGuid is set by Windows Setup and stable for the life of the
    // installation.
    std::optional<std::string> get() {
        HKEY key;
        if (RegOpenKeyExA(
                HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Cryptography", 0,
                KEY_READ | KEY_WOW64_64KEY, &key
            ) != ERROR_SUCCESS) {
            return std::nullopt;
        }

        char buffer[64];
        DWORD bufferSize = sizeof(buffer);
        const LONG queryResult = RegGetValueA(
            key, nullptr, "MachineGuid", RRF_RT_REG_SZ, nullptr, buffer, &bufferSize
        );
        RegCloseKey(key);
        if (queryResult != ERROR_SUCCESS) return std::nullopt;

        std::string id = trim(buffer);
        if (id.empty()) return std::nullopt;
        return id;
    }
#else
    std::optional<std::string> get() {
        return std::nullopt;
    }
#endif
}
