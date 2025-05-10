//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/game/SudokuGamePresenter.h"
#include "application/app_events/ButtonEvents.h"

void SudokuGamePresenter::onNewMove(const int value) {
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
    const int elapsedTime = Timestamp::now() - getCurrentGame()->getStartTime().value();
    int hours = elapsedTime / 3600;
    int minutes = elapsedTime % 3600 / 60;
    int seconds = elapsedTime % 60;
    std::string elapsed;
    if (hours) elapsed += std::format("{:02d}:", hours);
    elapsed += std::format("{:02d}:", minutes);
    elapsed += std::format("{:02d}", seconds);
    if (elapsed.empty()) elapsed = "00:00";
    return elapsed;
}

void SudokuGamePresenter::onBackButtonClicked() const {
    eventBus->publish(OnMainMenuButtonClicked());
}

void SudokuGamePresenter::onSurrenderButtonClicked() const {
    eventBus->publish(OnSudokuGameSurrendered());
}
