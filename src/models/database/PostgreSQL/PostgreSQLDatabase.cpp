#include <pqxx/pqxx>
#include <string>

#include "models/database/PostgreSQL/PostgreSQLDatabase.h"

#include <iostream>

PostgreSQLDatabase::PostgreSQLDatabase(const std::string &connString) {
    connectionString = connString;
    conn = nullptr;
    try {
        PostgreSQLDatabase::connect();
    } catch (const std::exception &e) {
        std::cerr << "PostgreSQLDatabase::PostgreSQLDatabase(): " << e.what() << std::endl;
        throw;
    }
}

PostgreSQLDatabase::~PostgreSQLDatabase() {
    printf("[PostgreSQLDatabase] Disconnecting from database...\n");
    PostgreSQLDatabase::disconnect();
}

bool PostgreSQLDatabase::connect() {
    try {
        conn = std::make_unique<pqxx::connection>(connectionString);
        printf(
            "[PostgreSQLDatabase] Connected to database %s on host %s:%s\n",
            conn->dbname(),
            conn->hostname(),
            conn->port()
        );
        return true;
    } catch (const std::exception &e) {
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

pqxx::result PostgreSQLDatabase::execute(IQuery<pqxx::params> &query) {
    pqxx::work txn(*conn);
    try {
        const pqxx::result result = txn.exec(query.getQueryString(), query.getQueryParameters());
        txn.commit();
        return result;
    } catch (const std::exception &e) {
        txn.abort();
        throw std::runtime_error("PostgreSQLDatabase::execute(): " + std::string(e.what()));
    }
}
