//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISUDOKUGAMEVIEW_H
#define ISUDOKUGAMEVIEW_H
#include "interfaces/IView.h"

class ISudokuGameView : public IView<class SudokuGamePresenter, ISudokuGameView> {
public:
    void render() override = 0;
};

#endif //ISUDOKUGAMEVIEW_H
