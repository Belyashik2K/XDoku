//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUDIFFICULTY_H
#define SUDOKUDIFFICULTY_H
#include <string>

enum class SudokuDifficultyEnum { EASY, MEDIUM, HARD, EXPERT };

struct SudokuDifficultySettings {
    int openCellsCount;
    std::string difficultyName;
};

class SudokuDifficulty {
public:
    static SudokuDifficultySettings getSettings(SudokuDifficultyEnum level);
    static SudokuDifficultyEnum fromString(const std::string &difficulty);
private:
    static int getOpenCellsCount(SudokuDifficultyEnum level);
    static std::string getDifficultyName(SudokuDifficultyEnum level);
};

#endif //SUDOKUDIFFICULTY_H
