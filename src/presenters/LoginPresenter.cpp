//
// Created by belyashik2k on 4/27/25.
//

#include "presenters/LoginPresenter.h"

#include <iostream>
#include <ostream>

void LoginPresenter::onLoginButtonClicked() {
    printf("Login button clicked with username: %s and password: %s\n", username, password);
}

void LoginPresenter::onSignUpButtonClicked() {
    printf("Switching to sign up view\n");
}