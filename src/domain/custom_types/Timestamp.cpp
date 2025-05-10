#include "domain/custom_types/Timestamp.h"

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

std::string Timestamp::operator-(const Timestamp &other) const {
    std::tm thisTm = timestamp;
    std::tm otherTm = other.timestamp;

    const auto thisTimeT = std::mktime(&thisTm);
    const auto otherTimeT = std::mktime(&otherTm);

    const auto diff = std::difftime(thisTimeT, otherTimeT);

    printf("[Timestamp] Difference: %f\n", diff);
    const int hours = static_cast<int>(diff) / 3600;
    const int minutes = static_cast<int>(diff) % 3600 / 60;
    const int seconds = static_cast<int>(diff) % 60;
    std::string diffStr = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
    return diffStr;
}
