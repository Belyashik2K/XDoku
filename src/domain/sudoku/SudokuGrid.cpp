//
// Created by Belyashik2K on 07.04.2025.
//

#include "domain/sudoku/SudokuGrid.h"
#include "domain/sudoku/SudokuCell.h"

#include <vector>

void SudokuGrid::updateMasks(const int row, const int col, const int value, const bool isSetting) {
    const int bit = 1 << (value - 1);
    const int boxIndex = (row / 3) * 3 + (col / 3);

    if (isSetting) {
        rowMasks[row] |= bit;
        colMasks[col] |= bit;
        boxMasks[boxIndex] |= bit;
    } else {
        rowMasks[row] &= ~bit;
        colMasks[col] &= ~bit;
        boxMasks[boxIndex] &= ~bit;
    }
}

bool SudokuGrid::setCellValue(const int row, const int col, const int value) {
    if (!isCellEditable(row, col)) {
        return false;
    }

    const int oldValue = cells[row][col].getValue();

    if (oldValue == value) {
        return true;
    }

    if (
        !isValueUniqueInRow(row, value) ||
        !isValueUniqueInColumn(col, value) ||
        !isValueUniqueInBox(row, col, value)
    ) {
        return false;
    }

    if (oldValue != 0) {
        updateMasks(row, col, oldValue, false);
    }

    cells[row][col].setValue(value);
    updateMasks(row, col, value, true);
    return true;
}