//
// Created by Belyashik2K on 02.05.2025.
//

#ifndef IMGUILEADERBOARDVIEW_H
#define IMGUILEADERBOARDVIEW_H
#include "presenters/LeaderboardPresenter.h"
#include "views/imgui/ImguiView.h"

class ImguiLeaderboardView final : public IImguiView {
    LeaderboardPresenter* presenter = nullptr;
public:
    void render();
    void printLoader() const;
    void renderLeaderboard() const;
    void setPresenter(LeaderboardPresenter *p) { presenter = p; } // TODO: Move it to abstract class with T
};

#endif //IMGUILEADERBOARDVIEW_H
