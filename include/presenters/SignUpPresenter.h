//
// Created by belyashik2k on 4/29/25.
//

#ifndef SIGNUPPRESENTER_H
#define SIGNUPPRESENTER_H
#include <memory>

#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "core/database/repositories/IUserRepository.h"
#include "views/ISignUpView.h"

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

class SignUpPresenter final :
        public IPresenter<ISignUpView, SignUpPresenter>,
        public std::enable_shared_from_this<SignUpPresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IUserRepository> userRepository;

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
    SignUpPresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IUserRepository> &userRepository
    ) : eventBus(eventBus), userRepository(userRepository) {
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
