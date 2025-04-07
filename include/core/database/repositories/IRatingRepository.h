//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IRATINGREPOSITORY_H
#define IRATINGREPOSITORY_H

#include <any>
#include <optional>
#include <string>

class IRatingRepository {
public:
    virtual ~IRatingRepository() = default;
    virtual std::optional<std::any> getLeaderboard(int limit) const = 0;
    virtual std::optional<std::any> getRatingHistoryByUserId(int userId, int limit) const = 0;
    virtual int createRatingHistoryRecord(
        int userId,
        std::optional<int> gameId,
        int rating,
        const std::string &comment
    ) const = 0;
};

#endif //IRATINGREPOSITORY_H
