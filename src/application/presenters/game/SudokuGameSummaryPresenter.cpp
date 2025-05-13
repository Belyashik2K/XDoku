//
// Created by belyashik2k on 5/10/25.
//

#include "application/presenters/game/SudokuGameSummaryPresenter.h"

void SudokuGameSummaryPresenter::onFinishGameButtonClicked() {
    printf("[SudokuGameSummaryPresenter] Finish game button clicked\n");
    resetNeedToPlaySound();
    eventBus->publish(OnSummaryViewClosed());
}