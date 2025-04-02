#include "models/custom_types/Timestamp.h"

#include <iomanip>

Timestamp::Timestamp(const std::string &timestampString) {
    std::istringstream ss(timestampString);

    ss >> std::get_time(&timestamp, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        throw std::invalid_argument("Timestamp::Timestamp(): Invalid timestamp string");
    }
}

std::string Timestamp::toString() const {
    std::ostringstream oss;
    oss << std::put_time(&timestamp, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
