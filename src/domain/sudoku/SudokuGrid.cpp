//
// Created by Belyashik2K on 07.04.2025.
//

#include "domain/sudoku/SudokuGrid.h"
#include "domain/sudoku/SudokuCell.h"

#include <vector>

const std::vector<std::vector<SudokuCell> > &SudokuGrid::getCells() const {
    return cells;
}

bool SudokuGrid::isValueUniqueInRow(const int row, const int value) const {
    if (value == 0) return true;
    for (int c = 0; c < 9; ++c) {
        if (cells[row][c].getValue() == value) return false;
    }
    return true;
}

bool SudokuGrid::isValueUniqueInColumn(const int col, const int value) const {
    if (value == 0) return true;
    for (int r = 0; r < 9; ++r) {
        if (cells[r][col].getValue() == value) return false;
    }
    return true;
}

bool SudokuGrid::isValueUniqueInBox(const int row, const int col, const int value) const {
    if (value == 0) return true;
    const int boxRowStart = row / 3 * 3;
    const int boxColStart = col / 3 * 3;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (cells[boxRowStart + r][boxColStart + c].getValue() == value)
                return false;
        }
    }
    return true;
}

int SudokuGrid::getCellValue(const int row, const int col) const {
    return cells[row][col].getValue();
}

bool SudokuGrid::isCellEditable(const int row, const int col) const {
    return cells[row][col].mayBeEdited();
}

bool SudokuGrid::isCellEmpty(const int row, const int col) const {
    return cells[row][col].isEmpty();
}

bool SudokuGrid::setCellValue(const int row, const int col, const int value) {
    if (!isCellEditable(row, col)) {
        return false;
    }

    if (
        !isValueUniqueInRow(row, value) ||
        !isValueUniqueInColumn(col, value) ||
        !isValueUniqueInBox(row, col, value)
    ) {
        return false;
    }

    cells[row][col].setValue(value);
    return true;
}

void SudokuGrid::lockCell(const int row, const int col) {
    cells[row][col].lock();
}

void SudokuGrid::fixCell(const int row, const int col) {
    cells[row][col].fix();
}

SudokuGrid::SudokuGrid() {
    cells.resize(9, std::vector<SudokuCell>(9));
}
