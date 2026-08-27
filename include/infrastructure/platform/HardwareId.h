//
// Created by belyashik2k on 8/27/26.
//

#ifndef HARDWAREID_H
#define HARDWAREID_H

#include <optional>
#include <string>

// A stable per-machine identifier, used by SessionManager to persist a login
// session across app launches. Implemented per-platform: there's no portable
// libc API for this.
namespace HardwareId {
    std::optional<std::string> get();
}

#endif //HARDWAREID_H
