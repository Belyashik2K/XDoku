//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H
#include <array>
#include <vector>

#include "SudokuCell.h"

#include "domain/sudoku/SudokuGrid.h"

#define COMPLETED_MASK 0b111111111

class SudokuGrid {
private:
    std::vector<std::vector<SudokuCell>> cells;

    std::array<int, 9> rowMasks = {};
    std::array<int, 9> colMasks = {};
    std::array<int, 9> boxMasks = {};

public:
    const std::vector<std::vector<SudokuCell>>& getCells() const {
        return cells;
    }

    void updateMasks(int row, int col, int value, bool isSetting);

    bool isValueUniqueInRow(const int row, const int value) const {
        if (value == 0) return true;
        return (rowMasks[row] & (1 << (value - 1))) == 0;
    }

    bool isValueUniqueInColumn(const int col, const int value) const {
        if (value == 0) return true;
        return (colMasks[col] & (1 << (value - 1))) == 0;
    }

    bool isValueUniqueInBox(const int row, const int col, const int value) const {
        if (value == 0) return true;
        const int boxIndex = (row / 3) * 3 + (col / 3);
        return (boxMasks[boxIndex] & (1 << (value - 1))) == 0;
    }

    bool isGridSolved() const {
        for (int i = 0; i < 9; ++i) {
            if (rowMasks[i] != COMPLETED_MASK || colMasks[i] != COMPLETED_MASK || boxMasks[i] != COMPLETED_MASK) {
                return false;
            }
        }
        return true;
    }

    int getCellValue(const int row, const int col) const {
        return cells[row][col].getValue();
    }

    bool isCellEditable(const int row, const int col) const {
        return cells[row][col].mayBeEdited();
    }

    bool isCellEmpty(const int row, const int col) const {
        return cells[row][col].isEmpty();
    }

    bool setCellValue(int row, int col, int value);

    void lockCell(const int row, const int col) {
        cells[row][col].lock();
    }

    void fixCell(const int row, const int col) {
        cells[row][col].fix();
    }

    SudokuGrid() {
        cells.resize(9, std::vector<SudokuCell>(9));
    }

    void resetMasks() {
        rowMasks.fill(0);
        colMasks.fill(0);
        boxMasks.fill(0);
    }
};


#endif //SUDOKUGRID_H
