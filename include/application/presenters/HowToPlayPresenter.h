//
// Created by belyashik2k on 5/3/25.
//

#ifndef HOWTOPLAYPRESENTER_H
#define HOWTOPLAYPRESENTER_H
#include <memory>

#include "application/EventBus.h"
#include "interfaces/IPresenter.h"
#include "interfaces/views/IHowToPlayView.h"

enum class FAQType {
    DIFFICULTY,
    CELL_SELECTION,
    NUMBER_PLACEMENT,
    OVERVIEW
};

class HowToPlayPresenter final :
        public IPresenter<IHowToPlayView> {
    std::shared_ptr<EventBus> eventBus;

    FAQType currentFAQType = FAQType::DIFFICULTY;
public:
    explicit HowToPlayPresenter(
        const std::shared_ptr<EventBus> &eventBus
    ) : eventBus(eventBus) {
    }

    void resetFAQType() {
        currentFAQType = FAQType::DIFFICULTY;
    }
    FAQType getCurrentFAQType() const {
        return currentFAQType;
    }

    void setNextFAQType();
    void onNextButtonClicked();
    void onBackButtonClicked();
};

#endif //HOWTOPLAYPRESENTER_H
