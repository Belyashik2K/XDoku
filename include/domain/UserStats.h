//
// Created by belyashik2k on 5/3/25.
//

#ifndef USERSTATS_H
#define USERSTATS_H
#include "sudoku/enums/SudokuDifficulty.h"

class UserStats {
    int totalGames = 0;
    int finishedGames = 0;
    int averageSolutionTimeSeconds = 0;
    SudokuDifficultyEnum mostCommonDifficulty = SudokuDifficultyEnum::UNKNOWN;

public:
    UserStats() = default;
    UserStats(
        const int totalGames,
        const int finishedGames,
        const int averageSolutionTimeSeconds,
        const SudokuDifficultyEnum mostCommonDifficulty
    ) :
        totalGames(totalGames),
        finishedGames(finishedGames),
        averageSolutionTimeSeconds(averageSolutionTimeSeconds),
        mostCommonDifficulty(mostCommonDifficulty) {}

    [[nodiscard]] int getTotalGames() const { return totalGames; }
    [[nodiscard]] int getFinishedGames() const { return finishedGames; }
    [[nodiscard]] int getAverageSolutionTimeSeconds() const { return averageSolutionTimeSeconds; }
    [[nodiscard]] SudokuDifficultyEnum getMostCommonDifficulty() const { return mostCommonDifficulty; }

    [[nodiscard]] int getCompletionRate() const {
        return totalGames == 0 ? 0.0 : static_cast<double>(finishedGames) / totalGames * 100.0;
    }
};


#endif //USERSTATS_H
