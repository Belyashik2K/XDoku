//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUSTATUS_H
#define SUDOKUSTATUS_H
#include <string>

enum class SudokuGameStatusEnum { IN_PROGRESS, FINISHED, SURRENDERED, EXITED };

class SudokuGameStatus {
public:
    static std::string toString(SudokuGameStatusEnum status) ;
    static SudokuGameStatusEnum fromString(const std::string &status);
};

#endif //SUDOKUSTATUS_H
