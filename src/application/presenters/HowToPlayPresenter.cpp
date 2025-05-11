//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/HowToPlayPresenter.h"

#include "application/app_events/ButtonEvents.h"

void HowToPlayPresenter::onBackButtonClicked() const {
    eventBus->publish(OnBackButtonClicked());
}
