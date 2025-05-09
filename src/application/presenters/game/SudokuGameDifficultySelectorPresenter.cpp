//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/game/SudokuGameDifficultySelectorPresenter.h"

#include "application/app_events/ButtonEvents.h"

void SudokuGameDifficultySelectorPresenter::onDifficultySelected(const SudokuDifficultyEnum difficulty) {
    printf("[SudokuGameDifficultySelectorPresenter] Difficulty selected: %d\n", difficulty);
}

void SudokuGameDifficultySelectorPresenter::onBackButtonClicked() {
    eventBus->publish(OnMainMenuButtonClicked());
}
