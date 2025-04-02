//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef POSTGRESQLDATABASE_H
#define POSTGRESQLDATABASE_H

#include <pqxx/pqxx>
#include "core/database/IDatabase.h"

class PostgreSQLDatabase : public IDatabase<pqxx::connection, pqxx::params> {
    std::string connectionString;
    std::unique_ptr<pqxx::connection> conn;

public:
    explicit PostgreSQLDatabase(const std::string& connString);

    ~PostgreSQLDatabase() override;

    bool connect() override;

    bool disconnect() override;

    bool isConnected() const override;

    bool execute(IQuery<pqxx::params> &query) override;
};

#endif //POSTGRESQLDATABASE_H
