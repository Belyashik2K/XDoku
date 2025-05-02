#include "models/custom_types/Timestamp.h"

#include <chrono>
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

Timestamp Timestamp::now() {
    const auto now = std::chrono::system_clock::now();
    const auto timeT = std::chrono::system_clock::to_time_t(now);
    const std::tm tm = *std::localtime(&timeT);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return Timestamp(oss.str());
}

bool Timestamp::operator>(const Timestamp &other) const {
    return std::difftime(std::mktime(const_cast<std::tm *>(&timestamp)), std::mktime(const_cast<std::tm *>(&other.timestamp))) > 0;
}

