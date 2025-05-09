//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/game/SudokuGamePresenter.h"

void SudokuGamePresenter::onNewMove(const int value){
    const bool isValid = gameManager->createMove(selectedRow, selectedCol, value);
    updateMoveStatus(isValid);
}
