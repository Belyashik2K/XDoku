//
// Created by belyashik2k on 5/3/25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <memory>

#include "SessionManager.h"
#include "application/EventBus.h"
#include "interfaces/database/repositories/IGameRepository.h"
#include "interfaces/database/repositories/IMoveRepository.h"

class SudokuGameManager {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IGameRepository> gameRepository;
    std::shared_ptr<IMoveRepository> moveRepository;
    std::shared_ptr<SessionManager> sessionManager;

    std::unique_ptr<SudokuGame> currentGame = nullptr;

    void loadActiveGame();

    void createSudokuGame(const SudokuDifficultyEnum &difficulty);

    void subscribeToEvents();

    void clearCurrentGame() {
        currentGame.reset();
    }

    void setCurrentGame(std::unique_ptr<SudokuGame> game) {
        currentGame = std::move(game);
    }


public:
    SudokuGameManager(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IGameRepository> &gameRepository,
        const std::shared_ptr<IMoveRepository> &moveRepository,
        const std::shared_ptr<SessionManager> &sessionManager
    ) : eventBus(eventBus), gameRepository(gameRepository), moveRepository(moveRepository), sessionManager(sessionManager) {
        subscribeToEvents();
    }

    [[nodiscard]] const SudokuGame *getCurrentGame() const {
        return currentGame.get();
    }

    bool createMove(int selected_row, int selected_col, int value) const;

    void findActiveGame() const;
};

#endif //GAMEMANAGER_H
