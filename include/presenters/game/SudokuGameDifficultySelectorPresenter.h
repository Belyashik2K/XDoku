//
// Created by belyashik2k on 5/3/25.
//

#ifndef SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
#define SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"

class SudokuGameDifficultySelectorPresenter final : public IPresenter {
    EventBus *eventBus = nullptr;
    void subscribeToEvents();
public:
    explicit SudokuGameDifficultySelectorPresenter(EventBus *eventBus) : eventBus(eventBus) {
        subscribeToEvents();
    }
};

#endif //SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
