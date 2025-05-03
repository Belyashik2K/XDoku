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

    void onPlayButtonClicked() const;

    void onProfileButtonClicked() const;

    void onLeaderboardButtonClicked() const;

    void onHowToPlayButtonClicked() const;

    void onExitButtonClicked() const;
};

#endif //MAINMENUPRESENTER_H
