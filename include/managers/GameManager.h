//
// Created by belyashik2k on 5/3/25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "core/EventBus.h"
#include "core/database/repositories/IGameRepository.h"

class GameManager {
    IGameRepository *gameRepository;
    EventBus *eventBus;

    void subscribeToEvents();
public:
    GameManager(
        EventBus *eventBus,
        IGameRepository *gameRepository
    ) : gameRepository(gameRepository), eventBus(eventBus) {
        subscribeToEvents();
    }
};

#endif //GAMEMANAGER_H
