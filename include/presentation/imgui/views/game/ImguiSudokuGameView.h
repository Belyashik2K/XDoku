//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUISUDOKUGAMEVIEW_H
#define IMGUISUDOKUGAMEVIEW_H
#include <imgui.h>

#include "interfaces/views/game/ISudokuGameView.h"

class ImguiSudokuGameView final: public ISudokuGameView {
public:
    void render() override;

    void renderGame() const;

    void renderLoading() const;

    void drawCells() const;

    static void drawGridLines(ImVec2 windowPos, float gridSize, float cellSize, ImDrawList *drawList) ;

    void drawCells(const ImVec2 &windowPos, float cellSize, ImDrawList *drawList) const;

    static void adjustLayoutParameters(ImVec2 &windowPos, ImVec2 &windowSize);

    void renderSudokuGrid() const;

    void handleKeyboardInput() const;

    void renderButtons() const;

    void renderStatistics() const;
};

#endif //IMGUISUDOKUGAMEVIEW_H
