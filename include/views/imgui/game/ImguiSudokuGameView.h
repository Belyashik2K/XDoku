//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUISUDOKUGAMEVIEW_H
#define IMGUISUDOKUGAMEVIEW_H

#include "views/imgui/ImguiView.h"
#include "presenters/game/SudokuGamePresenter.h"

class ImguiSudokuGameView final: public IImguiView {
    SudokuGamePresenter *presenter = nullptr;
public:
    void render() override;
    void setPresenter(SudokuGamePresenter *p) { presenter = p; }
};

#endif //IMGUISUDOKUGAMEVIEW_H
