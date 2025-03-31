//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef POSTGRESQLDATABASE_H
#define POSTGRESQLDATABASE_H
#include "../core/IDatabase.h"

class PostgreSQLDatabase: public IDatabase<pqxx::connection> {
private:
    std::string connectionString_;
public:
    PostgreSQLDatabase(const std::string& connectionString);
    ~PostgreSQLDatabase() override;

    pqxx::connection connect() override;
    bool disconnect() override;
    bool isConnected(const pqxx::connection &connection) override;

    bool createUser(const std::string& username, const std::string& password) override;
    bool authenticateUser(const std::string& username, const std::string& password) override;
};

#endif //POSTGRESQLDATABASE_H
