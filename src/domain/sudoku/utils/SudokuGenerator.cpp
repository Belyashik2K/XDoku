#include "domain/sudoku/utils/SudokuGenerator.h"

#include <random>
#include <chrono>
#include <optional>

#define EMPTY 0

std::optional<std::pair<int, int>> findEmptyCell(const SudokuGrid& grid) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid.getCellValue(row, col) == EMPTY) {
                return std::make_pair(row, col);
            }
        }
    }
    return std::nullopt;
}

template<typename T>
void SudokuGenerator::shuffle(std::vector<T> &arr) {
    static std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(arr.begin(), arr.end(), rng);
}

bool SudokuGenerator::hasUniqueSolution(SudokuGrid &grid) {
    int solutions = 0;
    SudokuGrid tempBoard = grid;
    solveWithCount(tempBoard, solutions, 2);
    return solutions == 1;
}

bool SudokuGenerator::isValid(const SudokuGrid& grid, int row, int col, int num) {
    for (int i = 0; i < 9; ++i) {
        if (grid.getCellValue(row, i) == num) {
            return false;
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (grid.getCellValue(i, col) == num) {
            return false;
        }
    }

    const int boxRow = row / 3 * 3;
    const int boxCol = col / 3 * 3;
    for (int i = boxRow; i < boxRow + 3; ++i) {
        for (int j = boxCol; j < boxCol + 3; ++j) {
            if (grid.getCellValue(i, j) == num) {
                return false;
            }
        }
    }
    return true;
}

bool SudokuGenerator::solve(SudokuGrid& grid) {
    auto emptyCell = findEmptyCell(grid);
    if (!emptyCell.has_value()) {
        return true;
    }

    auto [row, col] = emptyCell.value();
    std::vector nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(nums);

    for (const int num : nums) {
        if (isValid(grid, row, col, num)) {
            grid.setCellValue(row, col, num);
            
            if (solve(grid)) {
                return true;
            }
            
            grid.setCellValue(row, col, EMPTY);
        }
    }
    return false;
}

void SudokuGenerator::solveWithCount(SudokuGrid& grid, int &count, const int limit) {
    if (count >= limit) return;

    auto emptyCell = findEmptyCell(grid);
    if (!emptyCell.has_value()) {
        count++;
        return;
    }

    auto [row, col] = emptyCell.value();
    std::vector nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(nums);

    for (const int num : nums) {
        if (isValid(grid, row, col, num)) {
            grid.setCellValue(row, col, num);
            solveWithCount(grid, count, limit);
            if (count >= limit) return;
            grid.setCellValue(row, col, EMPTY);
        }
    }
}

int SudokuGenerator::getUniqueCandidate(const SudokuGrid& grid, int row, int col) {
    std::set<int> candidates;
    for (int num = 1; num <= 9; ++num) {
        if (isValid(grid, row, col, num)) {
            candidates.insert(num);
        }
    }

    for (const int num : candidates) {
        bool uniqueInRow = true, uniqueInCol = true, uniqueInBlock = true;

        for (int c = 0; c < 9; ++c) {
            if (c != col && grid.getCellValue(row, c) == EMPTY && isValid(grid, row, c, num)) {
                uniqueInRow = false;
                break;
            }
        }

        for (int r = 0; r < 9; ++r) {
            if (r != row && grid.getCellValue(r, col) == EMPTY && isValid(grid, r, col, num)) {
                uniqueInCol = false;
                break;
            }
        }

        const int boxRow = row / 3 * 3;
        const int boxCol = col / 3 * 3;
        for (int r = boxRow; r < boxRow + 3; ++r) {
            for (int c = boxCol; c < boxCol + 3; ++c) {
                if ((r != row || c != col) && grid.getCellValue(r, c) == EMPTY && isValid(grid, r, c, num)) {
                    uniqueInBlock = false;
                    break;
                }
            }
            if (!uniqueInBlock) break;
        }

        if (uniqueInRow || uniqueInCol || uniqueInBlock) {
            return num;
        }
    }
    return 0;
}

bool SudokuGenerator::solveByHumanLogic(SudokuGrid& grid) {
    bool progress = true;
    while (progress) {
        progress = false;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (grid.getCellValue(row, col) != EMPTY) continue;

                std::set<int> candidates;
                for (int num = 1; num <= 9; ++num) {
                    if (isValid(grid, row, col, num)) {
                        candidates.insert(num);
                    }
                }

                if (candidates.size() == 1) {
                    grid.setCellValue(row, col, *candidates.begin());
                    progress = true;
                }
            }
        }

        if (!progress) break;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (grid.getCellValue(row, col) != EMPTY) continue;

                if (const int unique = getUniqueCandidate(grid, row, col); unique != 0) {
                    grid.setCellValue(row, col, unique);
                    progress = true;
                }
            }
        }
    }

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid.getCellValue(row, col) == EMPTY) {
                return false;
            }
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

        if (SudokuGrid tempGrid = grid; !hasUniqueSolution(tempGrid) || !solveByHumanLogic(tempGrid)) {
            grid.setCellValue(row, col, backup);
        } else {
            removed++;
        }
    }
}

SudokuGrid SudokuGenerator::generateFullGrid() {
    SudokuGrid grid;

    std::vector nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    shuffle(nums);

    if (!fillGridRandomly(grid, nums)) {
        throw std::runtime_error("Не удалось сгенерировать полную сетку судоку.");
    }

    return grid;
}

bool SudokuGenerator::fillGridRandomly(SudokuGrid& grid, const std::vector<int>& nums) {
    auto emptyCell = findEmptyCell(grid);
    if (!emptyCell.has_value()) {
        return true;
    }

    auto [row, col] = emptyCell.value();

    std::vector<int> shuffledNums = nums;
    shuffle(shuffledNums);

    for (const int num : shuffledNums) {
        if (isValid(grid, row, col, num)) {
            grid.setCellValue(row, col, num);

            if (fillGridRandomly(grid, shuffledNums)) {
                return true;
            }

            grid.setCellValue(row, col, EMPTY);
        }
    }

    return false;
}

SudokuGrid SudokuGenerator::generate(const SudokuDifficultyEnum difficulty) {
    SudokuGrid grid = generateFullGrid();
    const auto [openCellsCount, strRepr] = SudokuDifficulty::getSettings(difficulty);
    removeNumbers(grid, openCellsCount);
    return grid;
}

SudokuGrid SudokuGenerator::getSolutionGrid(SudokuGrid grid) {
    if (solve(grid)) {
        return grid;
    }
    throw std::runtime_error("Не удалось найти решение судоку");
}