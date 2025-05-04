//
// Created by belyashik2k on 5/3/25.
//

#ifndef SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
#define SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"
#include <memory>

class SudokuGameDifficultySelectorPresenter final : public IPresenter {
    std::shared_ptr<EventBus> eventBus;
public:
    explicit SudokuGameDifficultySelectorPresenter(
        const std::shared_ptr<EventBus> &eventBus
    ) : eventBus(eventBus) {}
};

#endif //SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
