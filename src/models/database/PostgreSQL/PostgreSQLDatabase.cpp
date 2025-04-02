#include <pqxx/pqxx>
#include <string>

#include "models/database/PostgreSQL/PostgreSQLDatabase.h"

PostgreSQLDatabase::PostgreSQLDatabase(const std::string &connString) {
    connectionString = connString;
    conn = nullptr;
}

PostgreSQLDatabase::~PostgreSQLDatabase() {
    PostgreSQLDatabase::disconnect();
}

bool PostgreSQLDatabase::connect() {
    try {
        conn = std::make_unique<pqxx::connection>(connectionString);
        return true;
    } catch (const std::exception& e) {
        throw std::runtime_error("PostgreSQLDatabase::connect(): " + std::string(e.what()));
    }
}

bool PostgreSQLDatabase::disconnect() {
    if (isConnected()) {
        conn->close();
        conn.reset();
    }
    return true;
}

bool PostgreSQLDatabase::isConnected() const {
    return conn && conn->is_open();
}

bool PostgreSQLDatabase::execute(IQuery<pqxx::params> &query) {
    pqxx::work txn(*conn);
    try {
        txn.exec(query.getQueryString(), query.getQueryParameters());
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        txn.abort();
        throw std::runtime_error("PostgreSQLDatabase::execute(): " + std::string(e.what()));
    }
}

