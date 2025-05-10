//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
#define IMGUISUDOKUGAMEDIFFICULTYSELECTORVIEW_H

#include "interfaces/views/game/ISudokuGameDifficultySelectorView.h"

class ImguiSudokuGameDifficultySelectorView final : public ISudokuGameDifficultySelectorView {
public:
    void render() override;

    static void renderHeader();
    void renderDifficultyButtons() const;
};

#endif //IMGUISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
