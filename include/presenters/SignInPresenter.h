//
// Created by belyashik2k on 4/27/25.
//

#ifndef LOGINPRESENTER_H
#define LOGINPRESENTER_H

#include <string>

#include "core/EventBus.h"
#include "core/IPresenter.h"
#include "core/database/repositories/IUserRepository.h"

class SignInPresenter final : public IPresenter {
    EventBus *eventBus = nullptr;
    IUserRepository *userRepository = nullptr;

    char username[128] = "";
    char password[128] = "";

    bool incorrectLogin = false;

    static bool isPasswordValid(const std::string &password, const std::string &hash);
    void setIncorrectLogin(const bool incorrect) { incorrectLogin = incorrect; }

    bool authorizeUser(const std::string &username, const std::string &password) const;
public:
    explicit SignInPresenter(EventBus *eventBus, IUserRepository *userRepository) : eventBus(eventBus), userRepository(userRepository) {}

    void onLoginButtonClicked();
    void onSignUpButtonClicked() const;

    char *getUsername() { return username; }
    char *getPassword() { return password; }
    bool isIncorrectLogin() const { return incorrectLogin; }
    int getBufferSize() const { return sizeof(username); }
};

#endif //LOGINPRESENTER_H
