//
// Created by Belyashik2K on 07.04.2025.
//

#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include <models/database/PostgreSQL/PostgreSQLQuery.h>

PostgreSQLSessionRepository::PostgreSQLSessionRepository(std::shared_ptr<PostgreSQLDatabase> database) {
    this->database = std::move(database);
}


bool PostgreSQLSessionRepository::createSession(const int &userId, const std::string &sessionId) const {
    if (!database->isConnected()) {
        return false;
    }

    PostgreSQLQuery query("INSERT INTO sessions (user_id, hwid) VALUES ($1, $2)");
    query.addParameter(std::to_string(userId));
    query.addParameter(sessionId);

    const pqxx::result result = database->execute(query);
    return result.affected_rows() > 0;
}

std::optional<std::pair<int, Timestamp>> PostgreSQLSessionRepository::getUserIdAndSessionExpiration(const std::string &sessionId) const {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query("SELECT user_id, expires_at FROM sessions WHERE hwid = $1");
    query.addParameter(sessionId);
    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }
    const pqxx::row row = result[0];
    const int userId = row["user_id"].as<int>();
    const std::string expiration = row["expires_at"].as<std::string>();
    return std::make_pair(userId, Timestamp(expiration));
}


std::optional<int> PostgreSQLSessionRepository::getUserIdBySessionId(const std::string &sessionId) const {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT user_id
        FROM sessions
        WHERE hwid = $1
    )");
    query.addParameter(sessionId);

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }

    const pqxx::row row = result[0];
    return row["user_id"].as<int>();
}

bool PostgreSQLSessionRepository::deleteSession(const std::string &sessionId) const {
    if (!database->isConnected()) {
        return false;
    }
    PostgreSQLQuery query("DELETE FROM sessions WHERE hwid = $1");
    query.addParameter(sessionId);
    const pqxx::result result = database->execute(query);
    return result.affected_rows() > 0;
}

