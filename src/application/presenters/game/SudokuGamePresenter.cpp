//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/game/SudokuGamePresenter.h"

void SudokuGamePresenter::onNewMove(const int value){
    const bool isValid = gameManager->createMove(selectedRow, selectedCol, value);
    updateMoveStatus(isValid);
}

void SudokuGamePresenter::setSelectedCell(const int row, const int col) {
    if (getCurrentGame()->getCurrentGrid().isCellEditable(row, col)) {
        selectedRow = row;
        selectedCol = col;
    } else {
        selectedRow = NOT_SELECTED;
        selectedCol = NOT_SELECTED;
    }
}

std::pair<int, int> SudokuGamePresenter::getSelectedCell() const {
    return std::make_pair(selectedRow, selectedCol);
}

std::string SudokuGamePresenter::getGameStatus() const {
    return SudokuDifficulty::getDifficultyName(getCurrentGame()->getDifficulty());
}

std::string SudokuGamePresenter::getMistakesCount() const {
    return std::to_string(getCurrentGame()->getMistakesCount());
}

std::string SudokuGamePresenter::getElapsedTime() const {
    return "not implemented yet";
}


