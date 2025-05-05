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

class OnActiveSudokuGameFound : public IEvent {
public:
    SudokuGame game;
    explicit OnActiveSudokuGameFound(const SudokuGame &game) : game(game) {}
};
class OnActiveSudokuGameNotFound : public IEvent {};

#endif //USEREVENTS_H
