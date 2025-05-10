//
// Created by Belyashik2K on 07.04.2025.
//

#include "domain/sudoku/utils/SudokuGenerator.h"

#include <random>
#include <chrono>
#include <iostream>

#define EMPTY 0

template<typename T>
void SudokuGenerator::shuffle(std::vector<T> &arr) {
    static std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(arr.begin(), arr.end(), rng);
}

bool SudokuGenerator::hasUniqueSolution(const SudokuGrid &grid) {
    SudokuGrid tempBoard = grid;
    int solutions = 0;
    auto cells = tempBoard.getCells();
    solveWithCount(cells, solutions, 2);
    return solutions == 1;
}

bool SudokuGenerator::isValid(
    const std::vector<std::vector<SudokuCell> > &board,
    const int row,
    const int col,
    const int num
) {
    for (int i = 0; i < 9; ++i) {
        if (board[row][i].getValue() == num || board[i][col].getValue() == num)
            return false;
    }

    const int boxRow = row / 3 * 3;
    const int boxCol = col / 3 * 3;
    for (int i = boxRow; i < boxRow + 3; ++i) {
        for (int j = boxCol; j < boxCol + 3; ++j) {
            if (board[i][j].getValue() == num)
                return false;
        }
    }
    return true;
}

bool SudokuGenerator::solve(std::vector<std::vector<SudokuCell> > &board) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col].getValue() != EMPTY) continue;

            for (int num = 1; num <= 9; ++num) {
                if (isValid(board, row, col, num)) {
                    board[row][col].setValue(num);
                    if (solve(board)) return true;
                    board[row][col].setValue(EMPTY);
                }
            }
            return false;
        }
    }
    return true;
}

void SudokuGenerator::solveWithCount(std::vector<std::vector<SudokuCell> > &board, int &count, const int limit) {
    if (count >= limit) return;

    int emptyRow = -1, emptyCol = -1;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col].getValue() == EMPTY) {
                emptyRow = row;
                emptyCol = col;
                break;
            }
        }
        if (emptyRow != -1) break;
    }

    if (emptyRow == -1) {
        count++;
        return;
    }

    for (int num = 1; num <= 9; ++num) {
        if (isValid(board, emptyRow, emptyCol, num)) {
            board[emptyRow][emptyCol].setValue(num);
            solveWithCount(board, count, limit);
            if (count >= limit) return;
            board[emptyRow][emptyCol].setValue(EMPTY);
        }
    }
}

bool SudokuGenerator::isUniqueCandidate(
    const std::vector<std::vector<SudokuCell>> &board,
    const int row,
    const int col,
    const std::set<int> &candidates
) {
    for (const int num: candidates) {
        bool uniqueInRow = true, uniqueInCol = true, uniqueInBlock = true;

        for (int c = 0; c < 9; ++c) {
            if (c != col && board[row][c].getValue() == EMPTY && isValid(board, row, c, num)) {
                uniqueInRow = false;
                break;
            }
        }

        for (int r = 0; r < 9; ++r) {
            if (r != row && board[r][col].getValue() == EMPTY && isValid(board, r, col, num)) {
                uniqueInCol = false;
                break;
            }
        }

        const int boxRow = row / 3 * 3;
        const int boxCol = col / 3 * 3;
        for (int r = boxRow; r < boxRow + 3; ++r) {
            for (int c = boxCol; c < boxCol + 3; ++c) {
                if ((r != row || c != col) && board[r][c].getValue() == 0 && isValid(board, r, c, num)) {
                    uniqueInBlock = false;
                    break;
                }
            }
        }

        if (uniqueInRow || uniqueInCol || uniqueInBlock) return true;
    }

    return false;
}

bool SudokuGenerator::solveByHumanLogic(std::vector<std::vector<SudokuCell>> &board) {
    bool progress = true;

    while (progress) {
        progress = false;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col].getValue() != EMPTY) continue;

                std::set<int> candidates;
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        candidates.insert(num);
                    }
                }

                if (candidates.size() == 1) {
                    board[row][col].setValue(*candidates.begin());
                    progress = true;
                }
            }
        }

        if (!progress) break;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col].getValue() == EMPTY) continue;

                std::set<int> candidates;
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(board, row, col, num)) {
                        candidates.insert(num);
                    }
                }

                if (isUniqueCandidate(board, row, col, candidates)) {
                    board[row][col].setValue(*candidates.begin());
                    progress = true;
                }
            }
        }
    }

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col].getValue() == 0) return false;
        }
    }

    return true;
}

void SudokuGenerator::removeNumbers(SudokuGrid &grid, const int countOfOpenCells) {
    const int to_remove = 81 - countOfOpenCells;
    std::vector<std::pair<int, int>> positions;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            positions.emplace_back(i, j);
        }
    }

    shuffle(positions);

    int removed = 0;
    for (auto&[row, col] : positions) {
        if (removed >= to_remove) break;
        if (grid.getCellValue(row, col) == EMPTY) continue;

        const int backup = grid.getCellValue(row, col);
        grid.setCellValue(row, col, EMPTY);

        SudokuGrid tempGrid = grid;
        if (!hasUniqueSolution(tempGrid) /* || !solveByHumanLogic(tempGrid.getCells()) */) {
            grid.setCellValue(row, col, backup);
        } else {
            removed++;
        }
    }
}


SudokuGrid SudokuGenerator::generateFullGrid() {
    std::vector nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(nums);

    SudokuGrid grid;
    auto& cells = grid.getCells();

    for (int i = 0; i < 9; ++i) {
        grid.setCellValue(0, i, nums[i]);
        // cells[0][i] = SudokuCell(nums[i], true);
    }

    // if (!solve(cells)) {
    //     throw std::runtime_error("Не удалось сгенерировать сетку");
    // }

    return grid;
}


SudokuGrid SudokuGenerator::generate(const SudokuDifficultyEnum difficulty) {
    SudokuGrid grid = generateFullGrid();
    const auto [openCellsCount, strRepr] = SudokuDifficulty::getSettings(difficulty);
    removeNumbers(grid, openCellsCount);
    return grid;
}

SudokuGrid SudokuGenerator::getSolutionGrid(SudokuGrid grid) {
    if (auto cells = grid.getCells(); solve(cells)) {
        SudokuGrid solutionGrid;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                solutionGrid.setCellValue(i, j, cells[i][j].getValue());
            }
        }
        return solutionGrid;
    }
    throw std::runtime_error("Не удалось найти решение судоку");
}



void SudokuGenerator::print(SudokuGrid &grid) {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0 && i != 0) std::cout << "------+-------+------\n";
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0 && j != 0) std::cout << "| ";
            if (grid.getCells()[i][j].getValue() == EMPTY) {
                std::cout << ". ";
            } else {
                std::cout << grid.getCells()[i][j].getValue() << ' ';
            }
        }
        std::cout << '\n';
    }
}




