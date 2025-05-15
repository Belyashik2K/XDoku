//
// Created by belyashik2k on 4/27/25.
//

#ifndef LOGINPRESENTER_H
#define LOGINPRESENTER_H

#include <memory>
#include <string>

#include "application/EventBus.h"
#include "interfaces/IPresenter.h"
#include "interfaces/database/repositories/IUserRepository.h"
#include "interfaces/views/ISignInView.h"

enum SignInError {
    NO_SIGN_IN_ERROR,
    SIGN_IN_ALL_FIELDS_REQUIRED,
    INVALID_CREDENTIALS
};

class SignInPresenter final : public IPresenter<ISignInView, SignInPresenter>,
                              public std::enable_shared_from_this<SignInPresenter> {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IUserRepository> userRepository;

    char username[128] = "";
    char password[128] = "";

    SignInError signInError = NO_SIGN_IN_ERROR;

    static bool isPasswordValid(const std::string &password, const std::string &hash);

    void setSignInError(const SignInError error) {
        signInError = error;
    }

    void resetData() {
        username[0] = '\0';
        password[0] = '\0';
        setSignInError(NO_SIGN_IN_ERROR);
    }

    bool authorizeUser(const std::string &username, const std::string &password);

public:
    explicit SignInPresenter(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<IUserRepository> &userRepository
    ) : eventBus(eventBus), userRepository(userRepository) {
    }

    void onLoginButtonClicked();

    void onSignUpButtonClicked() const;

    char *getUsername() { return username; }
    char *getPassword() { return password; }
    int getBufferSize() const { return sizeof(username); }

    std::string getErrorMessage() const;

    void init(std::unique_ptr<ISignInView> &&view) override {
        this->setSelf(weak_from_this());
        this->setView(std::move(view));
    }
};

#endif //LOGINPRESENTER_H
