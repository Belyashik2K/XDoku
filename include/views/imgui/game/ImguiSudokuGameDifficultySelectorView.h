//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
#define IMGUISUDOKUGAMEDIFFICULTYSELECTORVIEW_H

#include "views/imgui/ImguiView.h"
#include "presenters/game/SudokuGameDifficultySelectorPresenter.h"

class ImguiSudokuGameDifficultySelectorView final : public IImguiView {
    SudokuGameDifficultySelectorPresenter *presenter = nullptr;
public:
    void render();
    void setPresenter(SudokuGameDifficultySelectorPresenter *p) { presenter = p; }
};

#endif //IMGUISUDOKUGAMEDIFFICULTYSELECTORVIEW_H
