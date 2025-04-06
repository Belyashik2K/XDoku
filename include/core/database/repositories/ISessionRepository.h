//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef ISESSIONREPOSITORY_H
#define ISESSIONREPOSITORY_H
#include <optional>
#include <string>

class ISessionRepository {
public:
    virtual ~ISessionRepository() = default;

    virtual bool createSession(const int &userId, const std::string &sessionId) const = 0;
    virtual std::optional<std::string> getUsernameBySessionId(const std::string &sessionId) const = 0;
};

#endif //ISESSIONREPOSITORY_H
