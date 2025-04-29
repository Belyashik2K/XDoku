//
// Created by belyashik2k on 4/29/25.
//

#ifndef REGISTERPRESENTER_H
#define REGISTERPRESENTER_H
#include "core/EventBus.h"
#include "core/IPresenter.h"

class SignUpPresenter final : public IPresenter {
    EventBus *eventBus = nullptr;

    char username[128] = "";
    char email[128] = "";
    char password[128] = "";
    char confirmPassword[128] = "";
public:
    SignUpPresenter(EventBus *bus) : eventBus(bus) {}

    void onSignUpButtonClicked() const;
    void onBackButtonClicked() const;
    char *getUsername() { return username; }
    char *getEmail() { return email; }
    char *getPassword() { return password; }
    char *getConfirmPassword() { return confirmPassword; }
    int getBufferSize() const { return sizeof(username); }
};

#endif //REGISTERPRESENTER_H
