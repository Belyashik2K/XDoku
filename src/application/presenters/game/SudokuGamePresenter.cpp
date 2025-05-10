//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/game/SudokuGamePresenter.h"
#include "application/app_events/ButtonEvents.h"

bool SudokuGamePresenter::onNewMove(const int value) {
    const bool isValid = gameManager->createMove(selectedRow, selectedCol, value);
    updateMoveStatus(isValid);
    if (isValid) {
        selectedRow = NOT_SELECTED;
        selectedCol = NOT_SELECTED;
    }

    if (gameManager->isGridComplete()) {
        // gameManager->finishGame();
        eventBus->publish(OnSudokuGameFinished());
    }
    return isValid;
}

void SudokuGamePresenter::OnEscapeButtonClicked() {
    unselectCell();
}

void SudokuGamePresenter::unselectCell() {
    selectedRow = NOT_SELECTED;
    selectedCol = NOT_SELECTED;
}

void SudokuGamePresenter::setSelectedCell(const int row, const int col) {
    if (getCurrentGame()->getCurrentGrid().isCellEditable(row, col)) {
        selectedRow = row;
        selectedCol = col;
        validMove = true;
        return;
    }
    unselectCell();
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
    return getCurrentGame()->getElapsedTimeAsString();
}

void SudokuGamePresenter::onBackButtonClicked() const {
    eventBus->publish(OnMainMenuButtonClicked());
}

void SudokuGamePresenter::onSurrenderButtonClicked() const {
    eventBus->publish(OnSudokuGameSurrendered());
}
