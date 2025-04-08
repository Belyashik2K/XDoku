//
// Created by Belyashik2K on 07.04.2025.
//

#ifndef POSTGRESQLRATINGREPOSITORY_H
#define POSTGRESQLRATINGREPOSITORY_H

#include "core/database/repositories/IRatingRepository.h"
#include "models/database/PostgreSQL/PostgreSQLDatabase.h"

class PostgreSQLRatingRepository final : public IRatingRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    PostgreSQLRatingRepository(std::shared_ptr<PostgreSQLDatabase> database);
    std::optional<std::vector<LeaderboardPlace>> getLeaderboard(int limit) const override;
    int createRatingHistoryRecord(
        int userId,
        std::optional<int> gameId,
        int rating,
        const std::string &comment
    ) const override;
};

#endif //POSTGRESQLRATINGREPOSITORY_H
