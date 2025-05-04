//
// Created by belyashik2k on 5/3/25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "core/EventBus.h"
#include "core/database/repositories/IGameRepository.h"
#include "core/database/repositories/IMoveRepository.h"

class SudokuGameManager {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IGameRepository> gameRepository;
    std::shared_ptr<IMoveRepository> moveRepository;

    void getActiveGame() const;
    void subscribeToEvents() const;
public:
    SudokuGameManager(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IGameRepository> &gameRepository,
        const std::shared_ptr<IMoveRepository> &moveRepository
    ) : eventBus(eventBus), gameRepository(gameRepository), moveRepository(moveRepository) {
        subscribeToEvents();
    }
};

#endif //GAMEMANAGER_H
