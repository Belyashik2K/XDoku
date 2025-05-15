//
// Created by belyashik2k on 5/10/25.
//

#ifndef ISUDOKUGAMESUMMARYVIEW_H
#define ISUDOKUGAMESUMMARYVIEW_H
#include "interfaces/IView.h"

class ISudokuGameSummaryView : public IView<class SudokuGameSummaryPresenter, ISudokuGameSummaryView> {
public:
    void render() override = 0;
};

#endif //ISUDOKUGAMESUMMARYVIEW_H
