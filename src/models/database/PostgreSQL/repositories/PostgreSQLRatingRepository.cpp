//
// Created by Belyashik2K on 07.04.2025.
//

#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"

#include "models/database/PostgreSQL/PostgreSQLQuery.h"

PostgreSQLRatingRepository::PostgreSQLRatingRepository(std::shared_ptr<PostgreSQLDatabase> database) {
    this->database = std::move(database);
}

std::optional<std::any> PostgreSQLRatingRepository::getLeaderboard(int limit) const {
    return std::nullopt;
}

std::optional<std::any> PostgreSQLRatingRepository::getRatingHistoryByUserId(int userId, int limit) const {
    return std::nullopt;
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
