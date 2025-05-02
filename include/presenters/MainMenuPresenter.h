//
// Created by belyashik2k on 5/2/25.
//

#ifndef MAINMENUPRESENTER_H
#define MAINMENUPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"

class MainMenuPresenter final : public IPresenter {
    EventBus *eventBus = nullptr;
public:
    explicit MainMenuPresenter(EventBus *eventBus) : eventBus(eventBus) {}

    void onPlayButtonClicked();

    void onProfileButtonClicked();

    void onLeaderboardButtonClicked();

    void onHowToPlayButtonClicked();

    void onExitButtonClicked();
};

#endif //MAINMENUPRESENTER_H
