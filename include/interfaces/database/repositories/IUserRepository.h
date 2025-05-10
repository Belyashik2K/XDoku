//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H
#include <optional>
#include <string>

#include "domain/User.h"
#include "domain/custom_types/Timestamp.h"

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual std::optional<User> create(User newUser) = 0;
    virtual std::optional<User> get(const std::string& username) = 0;
    virtual std::optional<User> get(int id) = 0;
    virtual bool isUsernameTaken(const std::string& username) const = 0;
    virtual bool isEmailTaken(const std::string& email) const = 0;
    virtual std::string getHashedPassword(const std::string &username) const = 0;
};

#endif //IUSERREPOSITORY_H
