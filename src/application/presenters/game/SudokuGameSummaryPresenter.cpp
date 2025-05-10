//
// Created by belyashik2k on 5/10/25.
//

#include "application/presenters/game/SudokuGameSummaryPresenter.h"

void SudokuGameSummaryPresenter::onFinishGameButtonClicked() const {
    printf("[SudokuGameSummaryPresenter] Finish game button clicked\n");
    eventBus->publish(OnSummaryViewClosed());
}