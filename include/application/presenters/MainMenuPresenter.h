//
// Created by belyashik2k on 5/2/25.
//

#ifndef MAINMENUPRESENTER_H
#define MAINMENUPRESENTER_H
#include <memory>

#include "application/EventBus.h"
#include "interfaces/IPresenter.h"
#include "interfaces/views/IMainMenuView.h"

class MainMenuPresenter final : public IPresenter<IMainMenuView> {
    std::shared_ptr<EventBus> eventBus;
public:
    explicit MainMenuPresenter(
        const std::shared_ptr<EventBus> &eventBus
    ) : eventBus(eventBus) {
    }

    void onPlayButtonClicked() const;

    void onProfileButtonClicked() const;

    void onLeaderboardButtonClicked() const;

    void onHowToPlayButtonClicked() const;

    void onExitButtonClicked() const;
};

#endif //MAINMENUPRESENTER_H
