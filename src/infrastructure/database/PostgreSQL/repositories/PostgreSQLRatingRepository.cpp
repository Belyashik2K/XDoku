//
// Created by Belyashik2K on 07.04.2025.
//

#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"

#include "infrastructure/database/PostgreSQL/PostgreSQLQuery.h"

PostgreSQLRatingRepository::PostgreSQLRatingRepository(std::shared_ptr<PostgreSQLDatabase> database) {
    this->database = std::move(database);
}

std::optional<std::vector<LeaderboardPlace>> PostgreSQLRatingRepository::getLeaderboard(const int limit) const {
    if (!database->isConnected()) {
        return std::nullopt;
    }
    PostgreSQLQuery query(R"(
        SELECT
            ROW_NUMBER() OVER (ORDER BY lr.current_rating DESC) AS rank,
            u.username,
            lr.current_rating
        FROM (
            SELECT
                user_id,
                new_rating AS current_rating,
                ROW_NUMBER() OVER (PARTITION BY user_id ORDER BY id DESC) AS rn
            FROM rating_history
        ) AS lr
        JOIN users u ON lr.user_id = u.id
        WHERE lr.rn = 1
        ORDER BY rank
        LIMIT $1;
    )");
    query.addParameter(std::to_string(limit));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }
    std::vector<LeaderboardPlace> leaderboard;
    for (const auto &row: result) {
        const int place = row["rank"].as<int>();
        const auto username = row["username"].as<std::string>();
        const int rating = row["current_rating"].as<int>();
        leaderboard.emplace_back(place, username, rating);
    }
    return leaderboard;
}


int PostgreSQLRatingRepository::createRatingHistoryRecord(
    const int userId,
    const std::optional<int> gameId,
    const int rating,
    const std::string &comment
) const {
    if (!database->isConnected()) {
        return false;
    }

    PostgreSQLQuery query(R"(
        INSERT INTO rating_history (user_id, game_id, rating_change, comment, new_rating)
        VALUES (
            $1, $2, $3, $4,
            COALESCE(
                (SELECT new_rating FROM rating_history WHERE user_id = $1 ORDER BY id DESC LIMIT 1),
                0
            ) + $3
        )
        RETURNING new_rating
    )");
    query.addParameter(std::to_string(userId));
    query.addParameter(gameId.has_value() ? std::to_string(gameId.value()) : "");
    query.addParameter(std::to_string(rating));
    query.addParameter(comment);

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        throw std::runtime_error("Failed to create rating history record");
    }

    const int newRating = result[0]["new_rating"].as<int>();
    return newRating;
}
