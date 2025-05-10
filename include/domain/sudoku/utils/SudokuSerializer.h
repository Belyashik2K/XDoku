//
// Created by belyashik2k on 5/10/25.
//

#ifndef SUDOKUSERIALIZER_H
#define SUDOKUSERIALIZER_H
#include <json.hpp>
#include <string>

#include "domain/sudoku/SudokuGrid.h"

class SudokuGridSerializer {
public:
    static SudokuGrid loadGridFromJsonString(
        const std::string &grid
    );
    static nlohmann::json saveGridToJson(
        const SudokuGrid &grid
    );
};

#endif //SUDOKUSERIALIZER_H
