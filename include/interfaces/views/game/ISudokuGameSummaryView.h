//
// Created by belyashik2k on 5/10/25.
//

#ifndef ISUDOKUGAMESUMMARYVIEW_H
#define ISUDOKUGAMESUMMARYVIEW_H
#include "interfaces/IView.h"

class ISudokuGameSummaryView : public IView<class SudokuGameSummaryPresenter, ISudokuGameSummaryView>,
                               public std::enable_shared_from_this<ISudokuGameSummaryView> {
public:
    void render() override = 0;
    void init(std::unique_ptr<SudokuGameSummaryPresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //ISUDOKUGAMESUMMARYVIEW_H
