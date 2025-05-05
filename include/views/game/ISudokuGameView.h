//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISUDOKUGAMEVIEW_H
#define ISUDOKUGAMEVIEW_H
#include "core/IView.h"

class SudokuGamePresenter;

class ISudokuGameView : public IView<SudokuGamePresenter> {
public:
    void render() override = 0;
};

#endif //ISUDOKUGAMEVIEW_H
