//
// Created by belyashik2k on 4/29/25.
//

#ifndef SIGNUPPRESENTER_H
#define SIGNUPPRESENTER_H
#include <memory>

#include "application/EventBus.h"
#include "interfaces/IPresenter.h"
#include "interfaces/database/repositories/IUserRepository.h"
#include "interfaces/views/ISignUpView.h"

enum SignUpError {
    NO_ERROR,
    ALL_FIELDS_REQUIRED,
    USERNAME_TAKEN,
    EMAIL_TAKEN,
    PASSWORD_MISMATCH,
    INVALID_EMAIL,
    INVALID_USERNAME,
    SHOULD_BE_AT_LEAST_8_CHARACTERS,
    SHOULD_CONTAIN_AT_LEAST_1_UPPERCASE,
    SHOULD_CONTAIN_AT_LEAST_1_LOWERCASE,
    SHOULD_CONTAIN_AT_LEAST_1_NUMBER,
    SHOULD_CONTAIN_AT_LEAST_1_SPECIAL_CHARACTER,
    UNEXPECTED_ERROR
};

class SignUpPresenter final :
        public IPresenter<ISignUpView, SignUpPresenter>,
        public std::enable_shared_from_this<SignUpPresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IUserRepository> userRepository;

    char username[128] = "";
    char email[128] = "";
    char password[128] = "";
    char confirmPassword[128] = "";

    SignUpError singUpError = NO_ERROR;

    bool validateInputs(
        const std::string &username,
        const std::string &email,
        const std::string &password,
        const std::string &confirmPassword
    );

    bool validateUsername(const std::string &username);

    bool validateEmail(const std::string &email);

    bool validatePassword(const std::string &password, const std::string &confirmPassword);

    std::optional<User> createUser(
        const std::string &username,
        const std::string &email,
        const std::string &password
    ) const;

    void setSignUpError(const SignUpError error) {
        singUpError = error;
    }

public:
    SignUpPresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IUserRepository> &userRepository
    ) : eventBus(eventBus), userRepository(userRepository) {
    }

    void resetData() {
        username[0] = '\0';
        email[0] = '\0';
        password[0] = '\0';
        confirmPassword[0] = '\0';
        setSignUpError(NO_ERROR);
    }

    void onSignUpButtonClicked();

    void onBackButtonClicked() const;

    std::string getErrorMessage() const;

    char *getUsername() { return username; }
    char *getEmail() { return email; }
    char *getPassword() { return password; }
    char *getConfirmPassword() { return confirmPassword; }
    int getBufferSize() const { return sizeof(username); }

    void init(std::unique_ptr<ISignUpView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //SIGNUPPRESENTER_H
