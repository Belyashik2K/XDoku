//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

#include <unordered_set>

struct SudokuCell {
    int value;
    bool is_fixed;
    std::unordered_set<int> candidates;
    bool is_valid;
};

#endif //SUDOKUCELL_H
