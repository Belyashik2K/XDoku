//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
#define ISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
#include "interfaces/IView.h"

class ISudokuGameDifficultySelectorView : public IView<class SudokuGameDifficultySelectorPresenter> {
public:
    void render() override = 0;
};

#endif //ISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
