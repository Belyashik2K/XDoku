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
#include "interfaces/database/repositories/IRatingRepository.h"

class SudokuGameManager {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IGameRepository> gameRepository;
    std::shared_ptr<IMoveRepository> moveRepository;
    std::shared_ptr<IRatingRepository> ratingRepository;
    std::shared_ptr<SessionManager> sessionManager;

    std::unique_ptr<SudokuGame> currentGame = nullptr;

    void loadActiveGame();

    void createSudokuGame(const SudokuDifficultyEnum &difficulty);

    void subscribeToEvents();

    void clearCurrentGame() {
        if (!currentGame) {
            return;
        }
        currentGame.reset();
    }

    void setCurrentGame(std::unique_ptr<SudokuGame> game) {
        currentGame = std::move(game);
    }

    void findActiveGame() const;

    void updateRating(int ratingChange, const std::string &message) const;

public:
    SudokuGameManager(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IGameRepository> &gameRepository,
        const std::shared_ptr<IMoveRepository> &moveRepository,
        const std::shared_ptr<IRatingRepository> &ratingRepository,
        const std::shared_ptr<SessionManager> &sessionManager
    ) : eventBus(eventBus),
        gameRepository(gameRepository),
        moveRepository(moveRepository),
        ratingRepository(ratingRepository),
        sessionManager(sessionManager) {
        subscribeToEvents();
    }

    [[nodiscard]] const SudokuGame *getCurrentGame() const {
        return currentGame.get();
    }

    bool createMove(int selected_row, int selected_col, int value) const;

    bool isGridComplete() const;

    void surrenderGame() const;

    void finishGame() const;

    [[nodiscard]] int calculateRating() const;
};

#endif //GAMEMANAGER_H
