//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUDIFFICULTY_H
#define SUDOKUDIFFICULTY_H
#include <string>
#include <unordered_map>
#include <vector>

enum class SudokuDifficultyEnum { EASY, MEDIUM, HARD, EXPERT };

struct SudokuDifficultySettings {
    int openCellsCount;
    std::string difficultyName;
};

const std::unordered_map<std::string, SudokuDifficultyEnum> sudokuDifficultyMap = {
    {"easy", SudokuDifficultyEnum::EASY},
    {"medium", SudokuDifficultyEnum::MEDIUM},
    {"hard", SudokuDifficultyEnum::HARD},
    {"expert", SudokuDifficultyEnum::EXPERT}
};

class SudokuDifficulty {
public:

    static SudokuDifficultySettings getSettings(SudokuDifficultyEnum level);
    static SudokuDifficultyEnum fromString(const std::string &difficulty);
    static std::vector<std::string> getDifficultyNames() {
        return {
            "easy",
            "medium",
            "hard",
            "expert"
        };
    }
    static std::string getDifficultyName(SudokuDifficultyEnum level);
private:
    static int getOpenCellsCount(SudokuDifficultyEnum level);
};

#endif //SUDOKUDIFFICULTY_H
