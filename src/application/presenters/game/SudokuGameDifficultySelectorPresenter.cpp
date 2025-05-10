//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/game/SudokuGameDifficultySelectorPresenter.h"

#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"

void SudokuGameDifficultySelectorPresenter::onDifficultySelected(const SudokuDifficultyEnum difficulty) const {
    eventBus->publish(OnSudokuDifficultySelected(difficulty));
}

void SudokuGameDifficultySelectorPresenter::onBackButtonClicked() {
    eventBus->publish(OnMainMenuButtonClicked());
}
