//
// Created by belyashik2k on 5/5/25.
//

#include "application/presenters/ProfilePresenter.h"

#include "application/app_events/ButtonEvents.h"

void ProfilePresenter::onBackButtonClicked() const{
    eventBus->publish(OnMainMenuButtonClicked());
}

void ProfilePresenter::onLogoutButtonClicked() const{
    eventBus->publish(OnLogoutButtonClicked());
}