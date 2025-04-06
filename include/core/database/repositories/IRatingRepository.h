//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IRATINGREPOSITORY_H
#define IRATINGREPOSITORY_H

#include <any>
#include <optional>

class IRatingRepository {
public:
    virtual ~IRatingRepository() = default;

    virtual std::optional<std::any> getLeaderboard(int limit) const = 0;
    virtual std::optional<std::any> getRatingHistory(int userId, int limit) const = 0;
};

#endif //IRATINGREPOSITORY_H
