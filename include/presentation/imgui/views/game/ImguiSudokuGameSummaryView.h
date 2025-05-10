//
// Created by belyashik2k on 5/10/25.
//

#ifndef IMGUISUDOKUGAMESUMMARYVIEW_H
#define IMGUISUDOKUGAMESUMMARYVIEW_H
#include "interfaces/views/game/ISudokuGameSummaryView.h"

class ImguiSudokuGameSummaryView final : public ISudokuGameSummaryView {
    void render() override;
};

#endif //IMGUISUDOKUGAMESUMMARYVIEW_H
