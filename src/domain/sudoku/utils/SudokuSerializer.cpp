//
// Created by belyashik2k on 5/10/25.
//

#include "domain/sudoku/utils/SudokuSerializer.h"

SudokuGrid SudokuGridSerializer::loadGridFromJsonString(const std::string &grid) {
    nlohmann::json gridJson = nlohmann::json::parse(grid);
    SudokuGrid sudokuGrid;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            const int value = gridJson[i][j].get<int>();
            sudokuGrid.setCellValue(i, j, value);
            if (value != 0) {
                sudokuGrid.fixCell(i, j);
            }
        }
    }
    return sudokuGrid;
}

nlohmann::json SudokuGridSerializer::saveGridToJson(const SudokuGrid &grid) {
    nlohmann::json gridJson = nlohmann::json::array();

    for (int i = 0; i < 9; ++i) {
        nlohmann::json row;
        for (int j = 0; j < 9; ++j) {
            row.push_back(grid.getCellValue(i, j));
        }
        gridJson.push_back(row);
    }
    return gridJson;
}

