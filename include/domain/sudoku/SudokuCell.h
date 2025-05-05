//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

#include <unordered_set>

class SudokuCell {
public:
    explicit SudokuCell(int value = 0, bool is_fixed = false);
    bool mayBeEdited() const;
    bool givenValueInCandidates(int value) const;
    void setValue(int new_value);
    int getValue() const;
    void setValid(bool valid);
    bool isValid() const;
private:
    int value;
    bool is_fixed;
    std::unordered_set<int> candidates;
    bool is_valid;
    void generateCandidates();
};

#endif //SUDOKUCELL_H
