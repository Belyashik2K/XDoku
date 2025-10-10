#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <ctime>
#include <sstream>

class Timestamp {
    std::tm timestamp{};

public:
    explicit Timestamp(const std::string& timestampStr);
    std::string toString() const;

    static Timestamp now();

    bool operator>(const Timestamp& other) const;

    int operator-(const Timestamp &other) const;
};

#endif
