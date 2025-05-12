//
// Created by belyashik2k on 5/3/25.
//

#include "application/presenters/HowToPlayPresenter.h"

#include "application/app_events/ButtonEvents.h"

void HowToPlayPresenter::setNextFAQType() {
    if (currentFAQType == FAQType::OVERVIEW) {
        resetFAQType();
    } else {
        currentFAQType = static_cast<FAQType>(static_cast<int>(currentFAQType) + 1);
    }
}

void HowToPlayPresenter::onNextButtonClicked() {
    setNextFAQType();
}

void HowToPlayPresenter::onBackButtonClicked() {
    resetFAQType();
    eventBus->publish(OnBackButtonClicked());
}
