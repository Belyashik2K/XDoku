//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISUDOKUGAMEVIEW_H
#define ISUDOKUGAMEVIEW_H
#include "interfaces/IView.h"

class ISudokuGameView : public IView<class SudokuGamePresenter, ISudokuGameView>,
                       public std::enable_shared_from_this<ISudokuGameView> {
public:
    void render() override = 0;
    void init(std::unique_ptr<SudokuGamePresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //ISUDOKUGAMEVIEW_H
