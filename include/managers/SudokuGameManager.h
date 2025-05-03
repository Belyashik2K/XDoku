//
// Created by belyashik2k on 5/3/25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "core/EventBus.h"
#include "core/database/repositories/IGameRepository.h"
#include "core/database/repositories/IMoveRepository.h"

class SudokuGameManager {
    IGameRepository *gameRepository;
    IMoveRepository *moveRepository;
    EventBus *eventBus;

    void subscribeToEvents() const;
public:
    SudokuGameManager(
        EventBus *eventBus,
        IGameRepository *gameRepository,
        IMoveRepository *moveRepository
    ) : gameRepository(gameRepository), moveRepository(moveRepository), eventBus(eventBus) {
        subscribeToEvents();
    }
    void getActiveGame() const;
};

#endif //GAMEMANAGER_H
