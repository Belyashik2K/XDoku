//
// Created by Belyashik2K on 07.04.2025.
//

#include "domain/sudoku/SudokuGrid.h"
#include "domain/sudoku/SudokuCell.h"

#include <vector>

std::vector<std::vector<SudokuCell>> &SudokuGrid::getCells() {
    return cells;
}

std::vector<std::vector<SudokuCell>> SudokuGrid::getCells() const {
    return cells;
}

void SudokuGrid::setCells(const std::vector<std::vector<SudokuCell>> &newCells) {
    cells = newCells;
}

SudokuGrid::SudokuGrid() {
    cells.resize(9, std::vector<SudokuCell>(9));
}

