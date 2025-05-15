//
// Created by belyashik2k on 4/29/25.
//

#include "application/presenters/SignUpPresenter.h"

#include <regex>

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
        setSignUpError(ALL_FIELDS_REQUIRED);
        return false;
    }
    if (!validateUsername(username)) {
        return false;
    }
    if (!validateEmail(email)) {
        return false;

    }
    if (!validatePassword(password, confirmPassword)) {
        return false;

    }
    if (userRepository->isUsernameTaken(username)) {
        printf("[SignUpPresenter] User with this username already exists\n");
        setSignUpError(USERNAME_TAKEN);
        return false;
    }
    if (userRepository->isEmailTaken(email)) {
        printf("[SignUpPresenter] User with this email already exists\n");
        setSignUpError(EMAIL_TAKEN);
        return false;
    }
    printf("[SignUpPresenter] All inputs are valid\n");
    return true;
}

bool SignUpPresenter::validateUsername(const std::string &username) {
    for (const char &c: username) {
        if (!std::isalnum(c) && c != '_') {
            setSignUpError(INVALID_USERNAME);
            return false;
        }
    }
    return true;
}

bool SignUpPresenter::validateEmail(const std::string &email) {
    const std::regex emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z]{2,}$)");
    if (!std::regex_match(email, emailRegex)) {
        setSignUpError(INVALID_EMAIL);
        return false;
    }
    return true;
}

bool SignUpPresenter::validatePassword(
    const std::string &password,
    const std::string &confirmPassword
) {
    if (password != confirmPassword) {
        printf("[SignUpPresenter] Passwords do not match\n");
        setSignUpError(PASSWORD_MISMATCH);
        return false;
    }

    bool hasDigit = false;
    bool hasLower = false;
    bool hasUpper = false;
    bool hasSpecial = false;
    const bool lenGreaterOrEqual8 = password.length() >= 8;

    for (const char &c: password) {
        if (std::isdigit(c)) {
            hasDigit = true;
        } else if (std::islower(c)) {
            hasLower = true;
        } else if (std::isupper(c)) {
            hasUpper = true;
        } else if (std::ispunct(c)) {
            hasSpecial = true;
        }
    }

    if (!lenGreaterOrEqual8) {
        printf("[SignUpPresenter] Password should be at least 8 characters\n");
        setSignUpError(SHOULD_BE_AT_LEAST_8_CHARACTERS);
        return false;
    }
    if (!hasUpper) {
        printf("[SignUpPresenter] Password should contain at least 1 uppercase letter\n");
        setSignUpError(SHOULD_CONTAIN_AT_LEAST_1_UPPERCASE);
        return false;
    }
    if (!hasLower) {
        printf("[SignUpPresenter] Password should contain at least 1 lowercase letter\n");
        setSignUpError(SHOULD_CONTAIN_AT_LEAST_1_LOWERCASE);
        return false;
    }
    if (!hasDigit) {
        printf("[SignUpPresenter] Password should contain at least 1 digit\n");
        setSignUpError(SHOULD_CONTAIN_AT_LEAST_1_NUMBER);
        return false;
    }
    if (!hasSpecial) {
        printf("[SignUpPresenter] Password should contain at least 1 special character\n");
        setSignUpError(SHOULD_CONTAIN_AT_LEAST_1_SPECIAL_CHARACTER);
        return false;
    }

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
        resetData();
        eventBus->publish(OnUserLoggedIn(user.value().getId()));
    } else {
        printf("[SignUpPresenter] Failed to create user\n");
        setSignUpError(UNEXPECTED_ERROR);
    }
}

void SignUpPresenter::onBackButtonClicked() const {
    eventBus->publish(OnSignInButtonClicked());
}

std::string SignUpPresenter::getErrorMessage() const {
    switch (singUpError) {
        case NO_ERROR: return "";
        case ALL_FIELDS_REQUIRED: return "All fields are required";
        case USERNAME_TAKEN: return "Username is already taken";
        case EMAIL_TAKEN: return "Email is already taken";
        case PASSWORD_MISMATCH: return "Passwords do not match";
        case INVALID_EMAIL: return "Email is not valid";
        case INVALID_USERNAME: return "Username is not valid";
        case SHOULD_BE_AT_LEAST_8_CHARACTERS: return "Password should be at least 8 characters";
        case SHOULD_CONTAIN_AT_LEAST_1_UPPERCASE: return "Password should contain at least 1 uppercase letter";
        case SHOULD_CONTAIN_AT_LEAST_1_LOWERCASE: return "Password should contain at least 1 lowercase letter";
        case SHOULD_CONTAIN_AT_LEAST_1_NUMBER: return "Password should contain at least 1 digit";
        case SHOULD_CONTAIN_AT_LEAST_1_SPECIAL_CHARACTER: return "Password should contain at least 1 special character";
        default: return "Unknown error";
    }
}
