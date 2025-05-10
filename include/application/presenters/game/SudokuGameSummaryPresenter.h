//
// Created by belyashik2k on 5/10/25.
//

#ifndef SUDOKUGAMESUMMARYPRESENTER_H
#define SUDOKUGAMESUMMARYPRESENTER_H
#include "SudokuGamePresenter.h"

#include "interfaces/views/game/ISudokuGameSummaryView.h"

class SudokuGameSummaryPresenter final : public IPresenter<ISudokuGameSummaryView, SudokuGameSummaryPresenter>,
                                         public std::enable_shared_from_this<SudokuGameSummaryPresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<SudokuGameManager> gameManager;

public:
    explicit SudokuGameSummaryPresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<SudokuGameManager> &gameManager
    ) : eventBus(eventBus), gameManager(gameManager) {
    }

    void init(std::unique_ptr<ISudokuGameSummaryView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }

    void onFinishGameButtonClicked() const;
};

#endif //SUDOKUGAMESUMMARYPRESENTER_H
