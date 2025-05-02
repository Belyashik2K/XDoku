//
// Created by belyashik2k on 4/27/25.
//

#include "presenters/SignInPresenter.h"

#include <cstring>
#include <bcrypt/BCrypt.hpp>

#include "core/app_events/ButtonEvents.h"
#include "core/app_events/UserEvents.h"

void SignInPresenter::onLoginButtonClicked() {
    printf("Login button clicked with username: %s and password: %s\n", username, password);
    if (!strlen(username) || !strlen(password)) {
        printf("Username or password is empty\n");
        return;
    }
    const std::string hashedPassword = userRepository->getHashedPassword(std::string(username));
    if (BCrypt::validatePassword(std::string(password), hashedPassword)) {
        const std::optional<User> user = userRepository->get(std::string(username));
        if (user.has_value()) {
            printf("User authorized, username: %s, email: %s\n", user->getUsername().c_str(), user->getEmail().c_str());
        }
        eventBus->publish(OnUserLoggedIn());
    } else {
        printf("Invalid password\n");
    }
}

void SignInPresenter::onSignUpButtonClicked() const {
    eventBus->publish(OnSignUpButtonClicked());
}
