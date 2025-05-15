//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
#define ISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
#include "interfaces/IView.h"

class ISudokuGameDifficultySelectorView : public IView<class SudokuGameDifficultySelectorPresenter, ISudokuGameDifficultySelectorView>,
                                         public std::enable_shared_from_this<ISudokuGameDifficultySelectorView> {
public:
    void render() override = 0;
    void init(std::unique_ptr<SudokuGameDifficultySelectorPresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //ISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
