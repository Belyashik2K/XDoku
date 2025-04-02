//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <pqxx/pqxx>

#include "core/database/repositories/IUserRepository.h"
#include "models/database/PostgreSQL/PostgreSQLDatabase.h"

class PostgreSQLUserRepository : public IUserRepository<pqxx::connection, pqxx::params> {
public:
    explicit PostgreSQLUserRepository(std::shared_ptr<PostgreSQLDatabase> database): IUserRepository(std::move(database)) {}

    bool create(const std::string &username, const std::string &email, const std::string &password) override;
    bool authenticate(const std::string &username, const std::string &password) override;
};

#endif //USERREPOSITORY_H
