//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IRATINGREPOSITORY_H
#define IRATINGREPOSITORY_H

#include <any>
#include <optional>
#include <string>
#include <vector>

#include "domain/leaderboard/LeaderboardPlace.h"

class IRatingRepository {
public:
    virtual ~IRatingRepository() = default;
    virtual std::optional<std::vector<LeaderboardPlace>> getLeaderboard(int limit) const = 0;
    virtual int createRatingHistoryRecord(
        int userId,
        std::optional<int> gameId,
        int rating,
        const std::string &comment
    ) const = 0;
};

#endif //IRATINGREPOSITORY_H
