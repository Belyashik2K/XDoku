//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUISUDOKUGAMEVIEW_H
#define IMGUISUDOKUGAMEVIEW_H
#include "interfaces/views/game/ISudokuGameView.h"

class ImguiSudokuGameView final: public ISudokuGameView {
public:
    void render() override;
};

#endif //IMGUISUDOKUGAMEVIEW_H
