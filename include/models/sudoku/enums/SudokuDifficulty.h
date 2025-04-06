//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUDIFFICULTY_H
#define SUDOKUDIFFICULTY_H

enum class SudokuDifficultyEnum { Easy, Medium, Hard, Expert };

struct DifficultySettings {
    int emptyCellsCount;
};

class SudokuDifficulty {
public:
    static DifficultySettings getSettings(SudokuDifficultyEnum level);
};

#endif //SUDOKUDIFFICULTY_H
