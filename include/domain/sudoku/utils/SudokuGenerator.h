//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <vector>
#include <set>

#include "domain/sudoku/SudokuGrid.h"
#include "domain/sudoku/enums/SudokuDifficulty.h"

class SudokuGenerator {
public:
    SudokuGrid generate(SudokuDifficultyEnum difficulty);

    SudokuGrid getSolutionGrid(SudokuGrid grid);
private:
    SudokuGrid generateFullGrid();

    bool fillGridRandomly(SudokuGrid &grid, const std::vector<int> &nums);

    void removeNumbers(SudokuGrid &grid, int countOfOpenCells);

    bool hasUniqueSolution(SudokuGrid &grid);


    bool isValid(const SudokuGrid &grid, int row, int col, int num);

    template <typename T>
    void shuffle(std::vector<T> &arr);

    bool solve(SudokuGrid &grid);

    void solveWithCount(SudokuGrid &grid, int &count, int limit = 2);

    int getUniqueCandidate(const SudokuGrid &grid, int row, int col);

    bool solveByHumanLogic(SudokuGrid &grid);
    bool isUniqueCandidate(const std::vector<std::vector<SudokuCell>> &board, int row, int col, const std::set<int> &candidates) ;
};

#endif //SUDOKUGENERATOR_H
