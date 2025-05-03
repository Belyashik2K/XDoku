//
// Created by belyashik2k on 5/3/25.
//

#ifndef SUDOKUGAMEPRESENTER_H
#define SUDOKUGAMEPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "core/database/repositories/IGameRepository.h"
#include "core/database/repositories/IMoveRepository.h"

class SudokuGamePresenter final : public IPresenter {
    EventBus *eventBus = nullptr;
    IGameRepository *gameRepository = nullptr;
    IMoveRepository *moveRepository = nullptr;
    std::optional<SudokuGame> currentGame = std::nullopt;

    void setCurrentGame(const SudokuGame& game);
    void subscribeToEvents();
public:
    SudokuGamePresenter(
        EventBus *eventBus,
        IGameRepository *gameRepository,
        IMoveRepository *moveRepository
    ) : eventBus(eventBus), gameRepository(gameRepository), moveRepository(moveRepository) {
        subscribeToEvents();
    }
};

#endif //SUDOKUGAMEPRESENTER_H
