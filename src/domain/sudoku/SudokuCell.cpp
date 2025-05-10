//
// Created by Belyashik2K on 07.04.2025.
//

#include "domain/sudoku/SudokuCell.h"

#include <stdexcept>

SudokuCell::SudokuCell(const int value, const bool is_fixed)
    : value(value), is_fixed(is_fixed), is_locked(is_fixed) {
    if (value < 0 || value > 9) {
        throw std::invalid_argument("Value must be between 0 and 9");
    }
}

int SudokuCell::getValue() const {
    return value;
}

bool SudokuCell::mayBeEdited() const {
    return !(is_fixed || is_locked);
}

void SudokuCell::setValue(const int new_value) {
    if (new_value < 0 || new_value > 9) {
        throw std::invalid_argument("Value must be between 0 and 9");
    }
    if (!mayBeEdited()) {
        throw std::runtime_error("Cell is locked or fixed");
    }
    value = new_value;
}

bool SudokuCell::isEmpty() const {
    return value == 0;
}

void SudokuCell::lock() {
    is_locked = true;
}

void SudokuCell::fix() {
    is_fixed = true;
    is_locked = true;
}
