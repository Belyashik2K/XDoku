//
// Created by belyashik2k on 5/3/25.
//

#ifndef SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
#define SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
#include <memory>

#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "views/game/ISudokuGameDifficultySelectorView.h"

class SudokuGameDifficultySelectorPresenter final :
        public IPresenter<ISudokuGameDifficultySelectorView, SudokuGameDifficultySelectorPresenter>,
        public std::enable_shared_from_this<SudokuGameDifficultySelectorPresenter> {
    std::shared_ptr<EventBus> eventBus;

public:
    explicit SudokuGameDifficultySelectorPresenter(
        const std::shared_ptr<EventBus> &eventBus
    ) : eventBus(eventBus) {
    }

    void init(std::unique_ptr<ISudokuGameDifficultySelectorView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
