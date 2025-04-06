//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUDIFFICULTY_H
#define SUDOKUDIFFICULTY_H

enum class SudokuDifficultyEnum { Easy, Medium, Hard, Expert };

struct SudokuDifficultySettings {
    int openCellsCount;
};

class SudokuDifficulty {
public:
    static SudokuDifficultySettings getSettings(SudokuDifficultyEnum level);
private:
    static int getOpenCellsCount(SudokuDifficultyEnum level);
};

#endif //SUDOKUDIFFICULTY_H
