//
// Created by belyashik2k on 4/29/25.
//

#ifndef REGISTERPRESENTER_H
#define REGISTERPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "core/database/repositories/IUserRepository.h"

enum SignUpError {
    NO_ERROR,
    ALL_FIELDS_REQUIRED,
    USERNAME_TAKEN,
    EMAIL_TAKEN,
    PASSWORD_MISMATCH,
    INVALID_EMAIL,
    INVALID_USERNAME,
    WEAK_PASSWORD,
    UNEXPECTED_ERROR
};

class SignUpPresenter final : public IPresenter {
    EventBus *eventBus = nullptr;
    IUserRepository *userRepository = nullptr;

    char username[128] = "";
    char email[128] = "";
    char password[128] = "";
    char confirmPassword[128] = "";

    bool validateInputs(
        const std::string &username,
        const std::string &email,
        const std::string &password,
        const std::string &confirmPassword
    );

    std::optional<User> createUser(
        const std::string &username,
        const std::string &email,
        const std::string &password
    ) const;

    SignUpError error = NO_ERROR;

public:
    SignUpPresenter(EventBus *bus, IUserRepository *userRepos) : eventBus(bus), userRepository(userRepos) {
    }


    void onSignUpButtonClicked();

    void onBackButtonClicked() const;

    std::string getErrorMessage() const;

    char *getUsername() { return username; }
    char *getEmail() { return email; }
    char *getPassword() { return password; }
    char *getConfirmPassword() { return confirmPassword; }
    int getBufferSize() const { return sizeof(username); }
};

#endif //REGISTERPRESENTER_H
