//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H
#include <vector>

#include "SudokuCell.h"

class SudokuGrid {
    std::vector<std::vector<SudokuCell>> cells;

    [[nodiscard]] bool isValueUniqueInRow(int row, int value) const;
    [[nodiscard]] bool isValueUniqueInColumn(int col, int value) const;
    [[nodiscard]] bool isValueUniqueInBox(int row, int col, int value) const;
public:
    SudokuGrid();

    [[nodiscard]] int getCellValue(int row, int col) const;
    [[nodiscard]] bool isCellEditable(int row, int col) const;

    bool isCellEmpty(int row, int col) const;

    bool setCellValue(int row, int col, int value);
    void lockCell(int row, int col);

    [[nodiscard]] const std::vector<std::vector<SudokuCell>>& getCells() const;
};

#endif //SUDOKUGRID_H
