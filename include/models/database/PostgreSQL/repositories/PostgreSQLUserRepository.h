//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef POSTGRESQLUSERREPOSITORY_H
#define POSTGRESQLUSERREPOSITORY_H

#include <pqxx/pqxx>

#include "models/User.h"
#include "models/database/PostgreSQL/PostgreSQLDatabase.h"
#include "core/database/repositories/IUserRepository.h"

class PostgreSQLUserRepository : public IUserRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    PostgreSQLUserRepository(std::shared_ptr<PostgreSQLDatabase> database);

    std::optional<User> create(User newUser) override;
    std::optional<User> get(const std::string &username) const override;
    std::string getHashedPassword(const std::string &username) const override;
    bool createSession(const int &userId, const std::string &sessionId) const override;
    std::optional<std::string> getUsernameBySessionId(const std::string &sessionId) const override;
};

#endif //POSTGRESQLUSERREPOSITORY_H
