//
// Created by belyashik2k on 5/3/25.
//

#ifndef SUDOKUGAMEPRESENTER_H
#define SUDOKUGAMEPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "core/database/repositories/IGameRepository.h"
#include "core/database/repositories/IMoveRepository.h"
#include "views/game/ISudokuGameView.h"

class SudokuGamePresenter final :
        public IPresenter<ISudokuGameView, SudokuGamePresenter>,
        public std::enable_shared_from_this<SudokuGamePresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IGameRepository> gameRepository;
    std::shared_ptr<IMoveRepository> moveRepository;

    std::optional<SudokuGame> currentGame = std::nullopt;

    void setCurrentGame(const SudokuGame &game);

    void subscribeToEvents();

public:
    SudokuGamePresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IGameRepository> &gameRepository,
        const std::shared_ptr<IMoveRepository> &moveRepository
    ) : eventBus(eventBus), gameRepository(gameRepository), moveRepository(moveRepository) {
        subscribeToEvents();
    }

    void init(std::unique_ptr<ISudokuGameView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //SUDOKUGAMEPRESENTER_H
