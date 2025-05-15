//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUDIFFICULTY_H
#define SUDOKUDIFFICULTY_H
#include <string>
#include <unordered_map>
#include <vector>

enum class SudokuDifficultyEnum { TEST, EASY, MEDIUM, HARD, EXPERT, UNKNOWN };

struct SudokuDifficultySettings {
    int openCellsCount;
    std::string difficultyName;
    float ratingMultiplier;
};

const std::unordered_map<std::string, SudokuDifficultyEnum> sudokuDifficultyMap = {
    {"test", SudokuDifficultyEnum::TEST},
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
            "expert",
            "test",
        };
    }
    static std::string getDifficultyName(SudokuDifficultyEnum level);
private:
    static int getOpenCellsCount(SudokuDifficultyEnum level);
    static float getRatingMultiplier(SudokuDifficultyEnum level);
};

#endif //SUDOKUDIFFICULTY_H
