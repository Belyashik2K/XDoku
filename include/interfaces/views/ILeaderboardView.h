//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ILEADERBOARDVIEW_H
#define ILEADERBOARDVIEW_H
#include "interfaces/IView.h"

class ILeaderboardView : public IView<class LeaderboardPresenter, ILeaderboardView>,
                         public std::enable_shared_from_this<ILeaderboardView> {
public:
    void render() override = 0;
    void init(std::unique_ptr<LeaderboardPresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //ILEADERBOARDVIEW_H
