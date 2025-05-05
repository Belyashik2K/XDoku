//
// Created by Belyashik2K on 02.05.2025.
//

#ifndef IMGUILEADERBOARDVIEW_H
#define IMGUILEADERBOARDVIEW_H
#include "views/ILeaderboardView.h"

class ImguiLeaderboardView final : public ILeaderboardView {
public:
    void render() override;
    void printLoader() const;
    void renderLeaderboard() const;
};

#endif //IMGUILEADERBOARDVIEW_H
