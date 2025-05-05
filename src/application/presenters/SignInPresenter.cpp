//
// Created by belyashik2k on 4/27/25.
//

#include "application/presenters/SignInPresenter.h"
#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"

#include <cstring>
#include <bcrypt/BCrypt.hpp>

bool SignInPresenter::isPasswordValid(const std::string &password, const std::string &hash) {
    return BCrypt::validatePassword(password, hash);
}

bool SignInPresenter::authorizeUser(const std::string &username, const std::string &password) const {
    const std::optional<User> user = userRepository->get(username);
    if (!user.has_value()) {
        printf("[SignInPresenter] User not found\n");
        return false;
    }

    if (!isPasswordValid(password, user->getPasswordHash())) {
        printf("[SignInPresenter] Invalid password\n");
        return false;
    }

    eventBus->publish(OnUserLoggedIn(user.value().getId()));
    return true;
}


void SignInPresenter::onLoginButtonClicked() {
    printf("[SignInPresenter] Login button clicked\n");
    const auto usernameStr = std::string(username);
    const auto passwordStr = std::string(password);

    if (usernameStr.empty() || passwordStr.empty()) {
        return;
    }
    if (authorizeUser(usernameStr, passwordStr)) {
        printf("[SignInPresenter] User logged in successfully\n");
    } else {
        setIncorrectLogin(true);
    }
}

void SignInPresenter::onSignUpButtonClicked() const {
    eventBus->publish(OnSignUpButtonClicked());
}
