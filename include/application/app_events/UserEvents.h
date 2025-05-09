//
// Created by belyashik2k on 4/30/25.
//

#ifndef USEREVENTS_H
#define USEREVENTS_H

#include <interfaces/IEvent.h>
#include <domain/sudoku/SudokuGame.h>

class OnUserLoggedIn : public IEvent {
public:
    int userId;
    explicit OnUserLoggedIn(const int userId) : userId(userId) {}
};
class OnUserLoggedOut : public IEvent {};

class OnActiveSudokuGameFound : public IEvent {};
class OnActiveSudokuGameNotFound : public IEvent {};

class OnSudokuDifficultySelected : public IEvent {
public:
    SudokuDifficultyEnum difficulty;
    explicit OnSudokuDifficultySelected(const SudokuDifficultyEnum &difficulty) : difficulty(difficulty) {}
};

class OnSudokuGameCreated : public IEvent {};

#endif //USEREVENTS_H
