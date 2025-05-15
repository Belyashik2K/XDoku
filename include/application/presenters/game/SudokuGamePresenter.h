//
// Created by belyashik2k on 5/3/25.
//

#ifndef SUDOKUGAMEPRESENTER_H
#define SUDOKUGAMEPRESENTER_H

#include "application/EventBus.h"
#include "application/managers/SudokuGameManager.h"

#include "interfaces/IPresenter.h"
#include "interfaces/views/game/ISudokuGameView.h"

#define NOT_SELECTED (-1)

enum GameLoadingStatus {
    LOADING,
    LOADED,
};

class SudokuGamePresenter final : public IPresenter<ISudokuGameView> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<SudokuGameManager> gameManager;

    GameLoadingStatus loadingStatus = LOADING;

    int selectedRow = NOT_SELECTED;
    int selectedCol = NOT_SELECTED;
    bool validMove = true;
public:
    SudokuGamePresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<SudokuGameManager> &gameManager
    ) : eventBus(eventBus), gameManager(gameManager) {
    }

    void updateLoadingStatus(const GameLoadingStatus &status) {
        loadingStatus = status;
    }

    GameLoadingStatus getLoadingStatus() {
        if (getCurrentGame()) {
            updateLoadingStatus(LOADED);
        }
        return loadingStatus;
    }

    bool isValidMove() const {
        return validMove;
    }

    void updateMoveStatus(const bool isValid) {
        validMove = isValid;
    }

    const SudokuGame *getCurrentGame() const {
        return gameManager->getCurrentGame();
    }

    void unselectCell();

    void setSelectedCell(int row, int col);

    std::pair<int, int> getSelectedCell() const;

    bool onNewMove(int value);

    void OnEscapeButtonClicked();

    std::string getGameStatus() const;
    std::string getMistakesCount() const;
    std::string getElapsedTime() const;

    void onBackButtonClicked() const;

    void onSurrenderButtonClicked() const;
};

#endif //SUDOKUGAMEPRESENTER_H
