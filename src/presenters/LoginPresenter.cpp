//
// Created by belyashik2k on 4/27/25.
//

#include "presenters/LoginPresenter.h"

#include <iostream>
#include <ostream>

void LoginPresenter::onLoginButtonClicked(const std::string &username, const std::string &password) {
    printf("Login button clicked with username: %s and password: %s\n", username.c_str(), password.c_str());
}