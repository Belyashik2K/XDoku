//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IGAMEREPOSITORY_H
#define IGAMEREPOSITORY_H
#include <any>
#include <optional>

#include "models/sudoku/SudokuGame.h"


class IGameRepository {
public:
    virtual ~IGameRepository() = default;

    virtual std::optional<SudokuGame> createGame(
        int userId,
        SudokuGame game
    ) = 0;
    // virtual SudokuGame getGame(int gameId) = 0;
    // virtual SudokuGame getGameWithMoves(int gameId) = 0;
    // virtual bool updateGame(
    //     int gameId,
    //     std::optional<std::any> endTime,
    //     std::optional<std::any> status,
    //     std::optional<std::any> exited_while_solved
    // ) = 0;
    // virtual bool finishGame(
    //     SudokuGame game
    // ) = 0;
};

#endif //IGAMEREPOSITORY_H
