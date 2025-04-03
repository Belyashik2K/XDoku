#include <iostream>

#include "models/User.h"
#include "models/database/PostgreSQL/PostgreSQLQuery.h"
#include "models/database/PostgreSQL/repositories/UserRepository.h"

bool PostgreSQLUserRepository::create(
    const std::string &username,
    const std::string &email,
    const std::string &password
) {
    if (!database->isConnected()) {
        return false;
    }

    try {
        PostgreSQLQuery query(R"(
            WITH inserted_user AS (
                INSERT INTO users (username, email, password_hash)
                VALUES ($1, $2, $3)
                RETURNING id
            )
            INSERT INTO rating_history (user_id, rating_change, new_rating, comment)
            SELECT
                id,
                1000 AS rating_change,
                1000 AS new_rating,
                'Start rating after registration' AS comment
            FROM inserted_user;
        )");
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

    PostgreSQLQuery query(R"(
        SELECT
            u.id,
            u.username,
            u.email,
            u.password_hash,
            u.created_at,
            rh.new_rating AS rating
        FROM
            users u
        LEFT JOIN (
            SELECT
                user_id,
                new_rating
            FROM
                rating_history
            WHERE
                (user_id, timestamp) IN (
                    SELECT
                        user_id,
                        MAX(timestamp)
                    FROM
                        rating_history
                    GROUP BY
                        user_id
                )
        ) rh ON u.id = rh.user_id
        WHERE
            u.username = $1;
    )");
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
    const std::optional<int> rating = row["rating"].is_null()
                                          ? std::nullopt
                                          : std::make_optional(row["rating"].as<int>());

    return User(id, finalUsername, email, finalPasswordHash, rating, createdAt, false);
}

bool PostgreSQLUserRepository::createSession(const int &userId, const std::string &sessionId) const {
    if (!database->isConnected()) {
        return false;
    }

    PostgreSQLQuery query("INSERT INTO sessions (user_id, hwid) VALUES ($1, $2)");
    query.addParameter(std::to_string(userId));
    query.addParameter(sessionId);

    const pqxx::result result = database->execute(query);
    return result.affected_rows() > 0;
}

std::optional<std::string> PostgreSQLUserRepository::getUsernameBySessionId(const std::string &sessionId) const {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT u.username
        FROM sessions s
        JOIN users u ON s.user_id = u.id
        WHERE s.hwid = $1;
    )");
    query.addParameter(sessionId);

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }

    const pqxx::row row = result[0];
    return row["username"].as<std::string>();
}

