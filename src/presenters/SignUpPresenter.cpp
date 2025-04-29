//
// Created by belyashik2k on 4/29/25.
//

#include "presenters/SignUpPresenter.h"

#include "core/app_events/buttons.h"

void SignUpPresenter::onSignUpButtonClicked() const {
    printf("Sign up button clicked with username: %s, email: %s, password: %s, confirm password: %s\n",
           username, email, password, confirmPassword);
}

void SignUpPresenter::onBackButtonClicked() const {
    eventBus->publish(OnSignInButtonClicked());
}