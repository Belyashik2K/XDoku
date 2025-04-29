//
// Created by belyashik2k on 4/27/25.
//

#ifndef LOGINPRESENTER_H
#define LOGINPRESENTER_H

#include <string>

#include "core/EventBus.h"
#include "core/IPresenter.h"

class LoginPresenter final : public IPresenter {
    EventBus *eventBus = nullptr;

    char username[128] = "";
    char password[128] = "";

    bool findActiveSession();
    bool authorizeUser(const std::string &username, const std::string &password);
public:
    explicit LoginPresenter(EventBus *bus) : eventBus(bus) {}

    void onLoginButtonClicked();
    char *getUsername() { return username; }
    char *getPassword() { return password; }
};

#endif //LOGINPRESENTER_H
