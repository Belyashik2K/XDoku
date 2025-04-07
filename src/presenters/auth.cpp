//
// Created by Belyashik2K on 03.04.2025.
//
#include <bcrypt/BCrypt.hpp>

#include "utils.h"
#include "presenters/AuthPresenter.h"

void AuthPresenter::run() const {
    view->clearScreen();
    view->showWelcomeMessage();

    std::optional<std::string> hwid = getDeviceHWID();

    if (hwid.has_value()) {
        const std::optional<std::string> savedUsername = sessionRepository->getUsernameBySessionId(hwid.value());
        if (savedUsername.has_value()) {
            std::optional<User> user = userRepository->get(savedUsername.value());
            if (user.has_value()) {
                view->showText("Hello, " + user.value().getUsername() + "! You are already logged in.");
            }
            return;
        }
    }

    view->showAuthOptions();
    const int choice = view->getAuthChoice();

    if (choice == 1) {
        std::optional<User> user = authenticateUser();
        if (user.has_value()) {
            view->showText("Hello, " + user.value().getUsername() + "!");
        }
    } else if (choice == 2) {
        std::optional<User> user = registerUser();
        if (user.has_value()) {
            view->showText("Please, login to your account to continue");
        }
    }
}

std::optional<User> AuthPresenter::registerUser() const {
    try {
        view->clearScreen();
        auto [username, email, password] = view->getRegistrationData();
        const User newUser(username, email, password);
        std::optional<User> createdUser = userRepository->create(newUser);
        if (!createdUser.has_value()) {
            view->showRegistrationResult(false, "Failed to create user");
            return std::nullopt;
        }
        view->showRegistrationResult(true, "");
        return createdUser;
    } catch (const std::invalid_argument &e) {
        view->showRegistrationResult(false, e.what());
        return std::nullopt;
    } catch (const std::exception &e) {
        view->showRegistrationResult(false, "An error occurred during registration");
        return std::nullopt;
    }
}

std::optional<User> AuthPresenter::authenticateUser() const {
    view->clearScreen();

    auto [username, password] = view->getLoginCredentials();

    std::string hashedPassword = userRepository->getHashedPassword(username);
    const bool isPasswordValid = BCrypt::validatePassword(password, hashedPassword);
    if (!isPasswordValid) {
        view->showAuthenticationResult(false);
        return std::nullopt;
    }

    const std::optional<User> authenticatedUser = userRepository->get(username);

    std::optional<std::string> hwid = getDeviceHWID();
    if (hwid.has_value()) {
        sessionRepository->createSession(authenticatedUser.value().getId(), hwid.value());
    }

    view->showAuthenticationResult(true);
    return authenticatedUser;
}
