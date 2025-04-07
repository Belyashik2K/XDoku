//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IGAMEREPOSITORY_H
#define IGAMEREPOSITORY_H
#include <any>
#include <optional>


class IGameRepository {
public:
    virtual ~IGameRepository() = default;

    virtual std::any createGame(
        int userId,
        std::any board,
        std::any solution,
        std::any difficulty
    ) = 0;
    virtual std::any getGame(int gameId) = 0;
    virtual std::any getGameWithMoves(int gameId) = 0;
    virtual std::any updateGame(
        int gameId,
        std::optional<std::any> endTime,
        std::optional<std::any> status,
        std::optional<std::any> exited_while_solved
    ) = 0;
    virtual std::any finishGame(
        int gameId
    ) = 0;
};

#endif //IGAMEREPOSITORY_H
