//
// Created by belyashik2k on 5/10/25.
//

#ifndef SUDOKUGAMESUMMARYPRESENTER_H
#define SUDOKUGAMESUMMARYPRESENTER_H
#include "SudokuGamePresenter.h"

#include "interfaces/views/game/ISudokuGameSummaryView.h"

class SudokuGameSummaryPresenter final : public IPresenter<ISudokuGameSummaryView> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<SudokuGameManager> gameManager;

    bool needToPlaySound = true;

public:
    explicit SudokuGameSummaryPresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<SudokuGameManager> &gameManager
    ) : eventBus(eventBus), gameManager(gameManager) {
    }

    const SudokuGame *getCurrentGame() const {
        return gameManager->getCurrentGame();
    }

    std::string getDifficulty() const {
        return SudokuDifficulty::getDifficultyName(getCurrentGame()->getDifficulty());
    }

    int getMistakesCount() const {
        return getCurrentGame()->getMistakesCount();
    }

    void resetNeedToPlaySound() {
        needToPlaySound = true;
    }

    bool getNeedToPlaySound() {
        if (getCurrentGame()->getStatus() == SudokuGameStatusEnum::SURRENDERED) {
            return false;
        }

        if (needToPlaySound) {
            needToPlaySound = false;
            return true;
        }
        return false;
    }

    std::string getElapsedTime() const {
        return getCurrentGame()->getElapsedTimeAsString();
    }

    int getGainedRating() const {
        return gameManager->calculateRating();
    }

    void onFinishGameButtonClicked();
};

#endif //SUDOKUGAMESUMMARYPRESENTER_H
