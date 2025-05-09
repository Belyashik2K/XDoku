//
// Created by belyashik2k on 5/3/25.
//

#ifndef SUDOKUGAMEPRESENTER_H
#define SUDOKUGAMEPRESENTER_H

#include "application/EventBus.h"
#include "application/managers/SudokuGameManager.h"

#include "interfaces/IPresenter.h"
#include "interfaces/views/game/ISudokuGameView.h"

enum GameLoadingStatus {
    LOADING,
    LOADED,
};

class SudokuGamePresenter final :
        public IPresenter<ISudokuGameView, SudokuGamePresenter>,
        public std::enable_shared_from_this<SudokuGamePresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<SudokuGameManager> gameManager;

    GameLoadingStatus loadingStatus = LOADING;
    int selectedRow = -1;
    int selectedCol = -1;
public:
    SudokuGamePresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<SudokuGameManager> &gameManager
    ) : eventBus(eventBus), gameManager(gameManager) {
    }

    void init(std::unique_ptr<ISudokuGameView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
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

    const SudokuGame *getCurrentGame() const {
        return gameManager->getCurrentGame();
    }

    void setSelectedCell(int row, int col) {
        selectedRow = row;
        selectedCol = col;
    }

    std::pair<int, int> getSelectedCell() const {
        return std::make_pair(selectedRow, selectedCol);
    }
};

#endif //SUDOKUGAMEPRESENTER_H
