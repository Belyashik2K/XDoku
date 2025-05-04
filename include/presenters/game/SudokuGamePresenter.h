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
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IGameRepository> gameRepository;
    std::shared_ptr<IMoveRepository> moveRepository;

    std::optional<SudokuGame> currentGame = std::nullopt;

    void setCurrentGame(const SudokuGame& game);
    void subscribeToEvents();
public:
    SudokuGamePresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IGameRepository> &gameRepository,
        const std::shared_ptr<IMoveRepository> &moveRepository
    ) : eventBus(eventBus), gameRepository(gameRepository), moveRepository(moveRepository) {
        subscribeToEvents();
    }
};

#endif //SUDOKUGAMEPRESENTER_H
