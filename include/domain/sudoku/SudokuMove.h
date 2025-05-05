//
// Created by belyashik2k on 4/8/25.
//

#ifndef SUDOKUMOVE_H
#define SUDOKUMOVE_H
#include <optional>
#include <utility>

class SudokuMove {
    std::optional<int> id;
    int gameId;
    int row;
    int column;
    int value;
    bool isValid;

public:
    SudokuMove(
        int id,
        int gameId,
        int row,
        int column,
        int value,
        bool isValid
    );
    SudokuMove(
        int gameId,
        int row,
        int column,
        int value,
        bool isValid
    );
    std::optional<int> getId() const;
    int getGameId() const;
    std::pair<int, int> coords() const;
    int getValue() const;
    bool isValidMove() const;
};

#endif //SUDOKUMOVE_H
