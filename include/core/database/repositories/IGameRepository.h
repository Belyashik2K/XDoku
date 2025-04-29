//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IGAMEREPOSITORY_H
#define IGAMEREPOSITORY_H
#include <optional>

#include "models/sudoku/SudokuGame.h"


class IGameRepository {
public:
    virtual ~IGameRepository() = default;

    virtual std::optional<SudokuGame> createGame(
        int userId,
        SudokuGame game
    ) = 0;
    virtual std::optional<SudokuGame> getGame(int gameId) = 0;
};

#endif //IGAMEREPOSITORY_H
