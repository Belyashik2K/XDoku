//
// Created by belyashik2k on 4/8/25.
//

#include "domain/sudoku/SudokuMove.h"

SudokuMove::SudokuMove(
    const int id, const int gameId, const int row,
    const int column, const int value, const bool isValid
) : id(id), gameId(gameId), row(row), column(column),
    value(value), isValid(isValid) {
}

SudokuMove::SudokuMove(
    const int gameId, const int row, const int column,
    const int value, const bool isValid
) : id(std::nullopt), gameId(gameId), row(row), column(column),
    value(value), isValid(isValid) {
}

std::optional<int> SudokuMove::getId() const {
    if (id.has_value()) {
        return id;
    }
    return std::nullopt;
}

int SudokuMove::getValue() const {
    return value;
}

int SudokuMove::getGameId() const {
    return gameId;
}

bool SudokuMove::isValidMove() const {
    return isValid;
}

std::pair<int, int> SudokuMove::coords() const {
    return std::make_pair(row, column);
}
