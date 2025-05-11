//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef POSTGRESQLUSERREPOSITORY_H
#define POSTGRESQLUSERREPOSITORY_H
#include "domain/UserStats.h"
#include "infrastructure/database/PostgreSQL/PostgreSQLDatabase.h"
#include "interfaces/database/repositories/IUserRepository.h"

class PostgreSQLUserRepository final : public IUserRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLUserRepository(std::shared_ptr<PostgreSQLDatabase> database);

    std::optional<User> create(User newUser) override;
    std::optional<User> get(const std::string &username) override;
    std::optional<User> get(int id) override;
    bool isUsernameTaken(const std::string &username) const override;
    bool isEmailTaken(const std::string &email) const override;
    UserStats getUserStats(int userId) const override;
    std::string getHashedPassword(const std::string &username) const override;
};

#endif //POSTGRESQLUSERREPOSITORY_H
