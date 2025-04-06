//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H
#include <vector>

#include "SudokuCell.h"

class SudokuGrid {
    std::vector<std::vector<SudokuCell>> cells;
public:
    SudokuGrid();

    std::vector<std::vector<SudokuCell>> &getCells();
    std::vector<std::vector<SudokuCell>> getCells() const;
    void setCells(const std::vector<std::vector<SudokuCell>> &newCells);
};

#endif //SUDOKUGRID_H
