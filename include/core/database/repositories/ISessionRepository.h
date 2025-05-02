//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef ISESSIONREPOSITORY_H
#define ISESSIONREPOSITORY_H
#include <optional>
#include <string>

#include <models/custom_types/Timestamp.h>

class ISessionRepository {
public:
    virtual ~ISessionRepository() = default;

    virtual bool createSession(const int &userId, const std::string &sessionId) const = 0;
    virtual std::optional<std::pair<int, Timestamp>> getUserIdAndSessionExpiration(const std::string &sessionId) const = 0;
    virtual std::optional<int> getUserIdBySessionId(const std::string &sessionId) const = 0;
    virtual bool deleteSession(const std::string &sessionId) const = 0;
};

#endif //ISESSIONREPOSITORY_H
