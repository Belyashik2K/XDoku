#include "domain/sudoku/utils/SudokuGenerator.h"

#include <algorithm>
#include <array>
#include <bit>
#include <functional>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

constexpr int FULL_MASK = 0x3FE;
constexpr int BOX_INDEX(const int row, const int col) { return (row / 3) * 3 + (col / 3); }

struct ConstraintMasks {
    std::array<int, 9> row{};
    std::array<int, 9> col{};
    std::array<int, 9> box{};

    void reset() {
        row.fill(0);
        col.fill(0);
        box.fill(0);
    }

    void set(const int rowIdx,const int colIdx, const int valueBit) {
        const int boxIdx = BOX_INDEX(rowIdx, colIdx);
        row[rowIdx] |= valueBit;
        col[colIdx] |= valueBit;
        box[boxIdx] |= valueBit;
    }

    void unset(const int rowIdx, const int colIdx, const int valueBit) {
        const int boxIdx = BOX_INDEX(rowIdx, colIdx);
        row[rowIdx] ^= valueBit;
        col[colIdx] ^= valueBit;
        box[boxIdx] ^= valueBit;
    }

    [[nodiscard]] int availableMask(const int rowIdx, const int colIdx) const {
        return FULL_MASK & ~(row[rowIdx] | col[colIdx] | box[BOX_INDEX(rowIdx, colIdx)]);
    }
};

std::vector<int> maskToCandidates(int mask) {
    std::vector<int> out;
    while (mask) {
        const int bit = mask & -mask;
        out.push_back(bit);
        mask &= mask - 1;
    }
    return out;
}

bool fillWithBacktracking(
    std::array<std::array<int, 9>, 9> &buffer,
    ConstraintMasks &masks,
    const std::function<int()> &randomSeed,
    const int index = 0
) {
    if (index == 81) {
        return true;
    }
    const int row = index / 9;
    const int col = index % 9;
    const int available = masks.availableMask(row, col);
    if (available == 0) {
        return false;
    }

    auto candidates = maskToCandidates(available);
    std::ranges::shuffle(candidates, std::mt19937(randomSeed()));

    for (const int bit : candidates) {
        const int value = std::countr_zero(static_cast<unsigned>(bit));
        masks.set(row, col, bit);
        buffer[row][col] = value;

        if (fillWithBacktracking(buffer, masks, randomSeed, index + 1)) {
            return true;
        }

        masks.unset(row, col, bit);
        buffer[row][col] = 0;
    }
    return false;
}

bool countSolutions(
    SudokuGrid &grid,
    const int index,
    ConstraintMasks &masks,
    int &solutions,
    const int limit
) {
    if (solutions >= limit) {
        return true;
    }

    if (index == 81) {
        ++solutions;
        return solutions >= limit;
    }

    const int row = index / 9;
    const int col = index % 9;

    if (grid.getCellValue(row, col) != 0) {
        return countSolutions(grid, index + 1, masks, solutions, limit);
    }

    int available = masks.availableMask(row, col);
    while (available) {
        const int bit = available & -available;
        const int value = std::countr_zero(static_cast<unsigned>(bit));

        grid.setCellValue(row, col, value);
        masks.set(row, col, bit);

        countSolutions(grid, index + 1, masks, solutions, limit);

        grid.setCellValue(row, col, 0);
        masks.unset(row, col, bit);

        if (solutions >= limit) {
            return true;
        }

        available &= available - 1;
    }

    return false;
}

bool SudokuGenerator::applyRemoval(SudokuGrid &puzzle, int targetRemovals, std::mt19937 &rng) {
    std::vector<int> positions(81);
    std::iota(positions.begin(), positions.end(), 0);
    std::shuffle(positions.begin(), positions.end(), rng);

    int removed = 0;
    for (const int index : positions) {
        if (removed >= targetRemovals) break;
        const int row = index / 9;
        const int col = index % 9;
        if (puzzle.getCellValue(row, col) == 0) continue;

        const int backup = puzzle.getCellValue(row, col);
        puzzle.setCellValue(row, col, 0);
        if (hasUniqueSolution(puzzle)) {
            ++removed;
        } else {
            puzzle.setCellValue(row, col, backup);
        }
    }
    return removed >= targetRemovals;
}

std::pair<SudokuGrid, SudokuGrid> SudokuGenerator::generateGrid(int open_cells_count) {
    ConstraintMasks masks;
    masks.reset();
    std::array<std::array<int, 9>, 9> buffer{};
    std::mt19937 rng(std::random_device{}());
    auto seedFn = [&] { return rng(); };

    while (!fillWithBacktracking(buffer, masks, seedFn)) {
        masks.reset();
        for (auto &row : buffer) {
            row.fill(0);
        }
        rng.seed(std::random_device{}());
    }

    SudokuGrid solution;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            solution.setCellValue(row, col, buffer[row][col]);
        }
    }

    SudokuGrid puzzle = solution;
    const int cellsToClear = std::clamp(81 - open_cells_count, 0, 81);
    if (!applyRemoval(puzzle, cellsToClear, rng)) {
        return generateGrid(open_cells_count);
    }

    return {puzzle, solution};
}

void SudokuGenerator::buildMasksFromGrid(
    const SudokuGrid &grid,
    std::array<int, 9> &rowMask,
    std::array<int, 9> &colMask,
    std::array<int, 9> &boxMask
) {
    rowMask.fill(0);
    colMask.fill(0);
    boxMask.fill(0);
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            const int value = grid.getCellValue(row, col);
            if (value == 0) continue;
            const int bit = 1 << value;
            const int box = BOX_INDEX(row, col);
            rowMask[row] |= bit;
            colMask[col] |= bit;
            boxMask[box] |= bit;
        }
    }
}

bool SudokuGenerator::hasUniqueSolution(const SudokuGrid &grid) {
    SudokuGrid temp = grid;
    std::array<int, 9> rowMask{};
    std::array<int, 9> colMask{};
    std::array<int, 9> boxMask{};
    buildMasksFromGrid(temp, rowMask, colMask, boxMask);

    ConstraintMasks masks{rowMask, colMask, boxMask};
    int solutions = 0;
    countSolutions(temp, 0, masks, solutions, 2);
    return solutions == 1;
}

bool SudokuGenerator::solveWithLimit(SudokuGrid &grid, int &solutions, const int limit) {
    std::array<int, 9> rowMask{};
    std::array<int, 9> colMask{};
    std::array<int, 9> boxMask{};
    buildMasksFromGrid(grid, rowMask, colMask, boxMask);

    ConstraintMasks masks{rowMask, colMask, boxMask};
    return countSolutions(grid, 0, masks, solutions, limit);
}

std::pair<SudokuGrid, SudokuGrid>  SudokuGenerator::generate(const SudokuDifficultyEnum difficulty) {
    const auto [open_cells_count, str_repr, rating_multiplier] = SudokuDifficulty::getSettings(difficulty);
    return generateGrid(open_cells_count);
}