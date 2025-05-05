//
// Created by belyashik2k on 4/29/25.
//

#include "application/presenters/SignUpPresenter.h"
#include "application/app_events/ButtonEvents.h"
#include "application/app_events/UserEvents.h"

bool SignUpPresenter::validateInputs(
    const std::string &username,
    const std::string &email,
    const std::string &password,
    const std::string &confirmPassword
) {
    if (username.empty() || email.empty() || password.empty() || confirmPassword.empty()) {
        printf("[SignUpPresenter] All fields are required\n");
        error = ALL_FIELDS_REQUIRED;
        return false;
    }
    if (!User::validateUsername(username)) {
        printf("[SignUpPresenter] Username is not valid\n");
        error = INVALID_USERNAME;
        return false;
    }
    if (!User::validateEmail(email)) {
        printf("[SignUpPresenter] Email is not valid\n");
        error = INVALID_EMAIL;
        return false;

    }
    if (password != confirmPassword) {
        printf("[SignUpPresenter] Passwords do not match\n");
        error = PASSWORD_MISMATCH;
        return false;

    }
    if (!User::validatePassword(password)) {
        printf("[SignUpPresenter] Password is not valid\n");
        error = WEAK_PASSWORD;
        return false;

    }
    if (userRepository->isUsernameTaken(username)) {
        printf("[SignUpPresenter] User with this username already exists\n");
        error = USERNAME_TAKEN;
        return false;
    }
    if (userRepository->isEmailTaken(email)) {
        printf("[SignUpPresenter] User with this email already exists\n");
        error = EMAIL_TAKEN;
        return false;
    }
    printf("[SignUpPresenter] All inputs are valid\n");
    error = NO_ERROR;
    return true;
}

std::optional<User> SignUpPresenter::createUser(
    const std::string &username,
    const std::string &email,
    const std::string &password
) const {
    const User user(username, email, password);
    return userRepository->create(user);
}

void SignUpPresenter::onSignUpButtonClicked() {
    printf("[SignUpPresenter] Sign up button clicked\n");
    const auto usernameStr = std::string(username);
    const auto emailStr = std::string(email);
    const auto passwordStr = std::string(password);
    const auto confirmPasswordStr = std::string(confirmPassword);

    if (!validateInputs(usernameStr, emailStr, passwordStr, confirmPasswordStr)) {
        printf("[SignUpPresenter] Validation failed\n");
        return;
    }

    std::optional<User> user = createUser(usernameStr, emailStr, passwordStr);
    if (user) {
        printf("[SignUpPresenter] User created successfully\n");
        eventBus->publish(OnUserLoggedIn(user.value().getId()));
    } else {
        printf("[SignUpPresenter] Failed to create user\n");
        error = UNEXPECTED_ERROR;
    }
}

void SignUpPresenter::onBackButtonClicked() const {
    eventBus->publish(OnSignInButtonClicked());
}

std::string SignUpPresenter::getErrorMessage() const {
    switch (error) {
        case NO_ERROR: return "";
        case ALL_FIELDS_REQUIRED: return "All fields are required";
        case USERNAME_TAKEN: return "Username is already taken";
        case EMAIL_TAKEN: return "Email is already taken";
        case PASSWORD_MISMATCH: return "Passwords do not match";
        case INVALID_EMAIL: return "Email is not valid";
        case INVALID_USERNAME: return "Username is not valid";
        case WEAK_PASSWORD: return
                    "Password is too weak (good e.g. >>> 12345678aA!)";
        default: return "Unknown error";
    }
}
