//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ILEADERBOARDVIEW_H
#define ILEADERBOARDVIEW_H
#include "core/IView.h"

class ILeaderboardView : public IView<class LeaderboardPresenter> {
public:
    void render() override = 0;
};

#endif //ILEADERBOARDVIEW_H
