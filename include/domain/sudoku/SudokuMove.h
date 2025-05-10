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
        int value
    );
    [[nodiscard]] std::optional<int> getId() const;
    [[nodiscard]] int getGameId() const;
    [[nodiscard]] std::pair<int, int> coords() const;
    [[nodiscard]] int getValue() const;
    [[nodiscard]] bool isValidMove() const;
    void setValid(const bool valid) { isValid = valid; }
};

#endif //SUDOKUMOVE_H
