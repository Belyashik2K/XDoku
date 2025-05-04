//
// Created by belyashik2k on 5/2/25.
//

#ifndef MAINMENUPRESENTER_H
#define MAINMENUPRESENTER_H
#include <memory>

#include "core/EventBus.h"
#include "core/IPresenter.h"

class MainMenuPresenter final : public IPresenter {
    std::shared_ptr<EventBus> eventBus;
public:
    explicit MainMenuPresenter(
        const std::shared_ptr<EventBus> &eventBus
    ) : eventBus(eventBus) {}

    void onPlayButtonClicked() const;

    void onProfileButtonClicked() const;

    void onLeaderboardButtonClicked() const;

    void onHowToPlayButtonClicked() const;

    void onExitButtonClicked() const;
};

#endif //MAINMENUPRESENTER_H
