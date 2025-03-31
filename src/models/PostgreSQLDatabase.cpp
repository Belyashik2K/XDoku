#include <pqxx/pqxx>
#include "../../include/models/PostgreSQLDatabase.h"

PostgreSQLDatabase::PostgreSQLDatabase(const std::string &connectionString) {
    connectionString_ = connectionString;
}

PostgreSQLDatabase::~PostgreSQLDatabase() {
    PostgreSQLDatabase::disconnect();
}

pqxx::connection PostgreSQLDatabase::connect() {
    pqxx::connection connection(connectionString_);
    return connection;
}

bool PostgreSQLDatabase::disconnect() {
    return true;
}

bool PostgreSQLDatabase::isConnected(const pqxx::connection &connection) {
    return connection.is_open();
}

bool PostgreSQLDatabase::createUser(const std::string &username, const std::string &password) {
    return false;
}

bool PostgreSQLDatabase::authenticateUser(const std::string &username, const std::string &password) {
    return false;
}
