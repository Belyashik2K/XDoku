//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <vector>
#include <set>

#include "models/sudoku/SudokuGrid.h"
#include "models/sudoku/enums/SudokuDifficulty.h"

class SudokuGenerator {
public:
    SudokuGrid generate(SudokuDifficultyEnum difficulty);
    static void print(SudokuGrid &grid);
private:
    SudokuGrid generateFullGrid();
    void removeNumbers(SudokuGrid &grid, int countOfOpenCells);

    static bool hasUniqueSolution(const SudokuGrid &grid);


    static bool isValid(const std::vector<std::vector<SudokuCell>> &board, int row, int col, int num);

    template <typename T>
    void shuffle(std::vector<T> &arr);

    static bool solve(std::vector<std::vector<SudokuCell>> &board);

    static void solveWithCount(std::vector<std::vector<SudokuCell>> &board, int& count, int limit = 2);
    static bool solveByHumanLogic(std::vector<std::vector<SudokuCell>> &board);
    static bool isUniqueCandidate(const std::vector<std::vector<SudokuCell>> &board, int row, int col, const std::set<int> &candidates) ;
};

#endif //SUDOKUGENERATOR_H
