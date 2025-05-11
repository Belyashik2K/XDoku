//
// Created by belyashik2k on 5/11/25.
//

#ifndef IMGUIVIEWFACTORY_H
#define IMGUIVIEWFACTORY_H
#include "interfaces/views/IViewFactory.h"

class ImguiViewFactory final : IViewFactory {
    void createLeaderboardView() override;
    void createProfileView() override;
    void createMainMenuView() override;
    void createSignInView() override;
    void createSignUpView() override;
    void createSudokuGameView() override;
    void createHowToPlayView() override;
    void createSudokuGameSummaryView() override;
    void createSudokuGameDifficultySelectorView() override;
};

#endif //IMGUIVIEWFACTORY_H
