//
// Created by belyashik2k on 5/3/25.
//

#ifndef SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
#define SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
#include <memory>

#include "application/EventBus.h"
#include "domain/sudoku/enums/SudokuDifficulty.h"
#include "interfaces/IPresenter.h"
#include "interfaces/views/game/ISudokuGameDifficultySelectorView.h"

class SudokuGameDifficultySelectorPresenter final : public IPresenter<ISudokuGameDifficultySelectorView> {
    std::shared_ptr<EventBus> eventBus;

public:
    explicit SudokuGameDifficultySelectorPresenter(
        const std::shared_ptr<EventBus> &eventBus
    ) : eventBus(eventBus) {
    }

    void onDifficultySelected(SudokuDifficultyEnum difficulty) const;

    void onBackButtonClicked() const;
};

#endif //SUDOKUGAMEDIFFICULTYSELECTORPRESENTER_H
