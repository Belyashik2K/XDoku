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

    bool findActiveSession();
    bool authorizeUser(const std::string &username, const std::string &password);
public:
    explicit SignInPresenter(EventBus *bus, IUserRepository *userRepos) : eventBus(bus), userRepository(userRepos) {}

    void onLoginButtonClicked();
    void onSignUpButtonClicked() const;

    char *getUsername() { return username; }
    char *getPassword() { return password; }
    int getBufferSize() const { return sizeof(username); }
};

#endif //LOGINPRESENTER_H
