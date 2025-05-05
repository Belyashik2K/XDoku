//
// Created by Belyashik2K on 07.04.2025.
//

#include "domain/sudoku/SudokuCell.h"

#include <stdexcept>

SudokuCell::SudokuCell(const int value, const bool is_fixed)
    : value(value), is_fixed(is_fixed), is_valid(true) {
    if (value < 0 || value > 9) {
        throw std::invalid_argument("Value must be between 0 and 9");
    }
    generateCandidates();
}

void SudokuCell::generateCandidates() {
    if (is_fixed) {
        return;
    }
    candidates.clear();
    for (int i = 1; i <= 9; ++i) {
        candidates.insert(i);
    }
}

int SudokuCell::getValue() const {
    return value;
}

bool SudokuCell::mayBeEdited() const {
    return !is_fixed;
}

bool SudokuCell::isValid() const {
    return is_valid;
}

void SudokuCell::setValue(const int new_value) {
    if (new_value < 0 || new_value > 9) {
        throw std::invalid_argument("Value must be between 0 and 9");
    }
    value = new_value;
    is_fixed = true;
    is_valid = true;
    candidates.clear();
}

bool SudokuCell::givenValueInCandidates(const int value) const {
    return candidates.contains(value);
}

void SudokuCell::setValid(const bool valid) {
    is_valid = valid;
}