//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUCELL_H
#define SUDOKUCELL_H

class SudokuCell {
public:
    explicit SudokuCell(int value = 0, bool is_fixed = false);

    [[nodiscard]] bool mayBeEdited() const;
    [[nodiscard]] int getValue() const;
    [[nodiscard]] bool isEmpty() const;

    void setValue(int new_value);
    void lock();
    void fix();

private:
    int value;

    bool is_fixed;
    bool is_locked;
};

#endif //SUDOKUCELL_H
