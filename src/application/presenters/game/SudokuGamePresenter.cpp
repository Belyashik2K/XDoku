//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/game/SudokuGamePresenter.h"
#include "application/app_events/UserEvents.h"

void SudokuGamePresenter::setCurrentGame(const SudokuGame& game) {
    printf("[SudokuGamePresenter] Setting current game\n");
    this->currentGame = game;
    // currentGame.value().printInfo();
}

void SudokuGamePresenter::subscribeToEvents() {
    eventBus->subscribe<OnActiveSudokuGameFound>(
        [this](const OnActiveSudokuGameFound &event) {
            this->setCurrentGame(event.game);
        }
    );
}
