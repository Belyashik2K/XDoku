//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H
#include <string>

#include "models/User.h"

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual std::optional<User> create(User newUser) = 0;
    virtual std::optional<User> get(const std::string& username) const = 0;
    virtual std::string getHashedPassword(const std::string &username) const = 0;
    virtual bool createSession(const int &userId, const std::string &sessionId) const = 0; // TODO: Move to SessionRepository
    virtual std::optional<std::string> getUsernameBySessionId(const std::string &sessionId) const = 0; // TODO: Move to SessionRepository
};

#endif //IUSERREPOSITORY_H
