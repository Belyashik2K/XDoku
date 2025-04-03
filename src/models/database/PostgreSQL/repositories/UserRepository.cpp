#include "models/database/PostgreSQL/repositories/UserRepository.h"

#include <iostream>

#include "models/User.h"
#include "models/database/PostgreSQL/PostgreSQLQuery.h"

bool PostgreSQLUserRepository::create(
    const std::string &username,
    const std::string &email,
    const std::string &password
) {
    if (!database->isConnected()) {
        return false;
    }

    try {
        PostgreSQLQuery query("INSERT INTO users (username, email, password_hash) VALUES ($1, $2, $3)");
        query.addParameter(username);
        query.addParameter(email);
        query.addParameter(password);

        const pqxx::result result = database->execute(query);
        return result.affected_rows() > 0;
    } catch (const std::exception &e) {
        std::cout << "PostgreSQLUserRepository::create(): " << e.what() << std::endl;
        return false;
    }
}

std::string PostgreSQLUserRepository::getHashedPassword(const std::string &username) const {
    if (!database->isConnected()) {
        throw std::runtime_error("Database is not connected");
    }
    PostgreSQLQuery query("SELECT password_hash FROM users WHERE username = $1");
    query.addParameter(username);

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        throw std::invalid_argument("User not found");
    }

    const pqxx::row row = result[0];

    return row["password_hash"].as<std::string>();
}

User PostgreSQLUserRepository::get(const std::string &username) const {
    if (!database->isConnected()) {
        throw std::runtime_error("Database is not connected");
    }

    PostgreSQLQuery query("SELECT id, username, email, password_hash, created_at FROM users WHERE username = $1");
    query.addParameter(username);

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        throw std::invalid_argument("User not found");
    }

    const pqxx::row row = result[0];

    int id = row["id"].as<int>();
    auto finalUsername = row["username"].as<std::string>();
    auto email = row["email"].as<std::string>();
    auto finalPasswordHash = row["password_hash"].as<std::string>();
    const auto createdAt = row["created_at"].as<std::string>();

    return User(id, finalUsername, email, finalPasswordHash, createdAt, false);
}
