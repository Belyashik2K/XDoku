//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef AUTHVIEW_H
#define AUTHVIEW_H
#include <string>

#include "core/IView.h"

class IAuthView : public IView {
public:
    virtual void render() const = 0;
    virtual void showText(const std::string& text) const = 0;
    virtual void clearScreen() const = 0;
    virtual void showWelcomeMessage() const = 0;
    virtual std::pair<std::string, std::string> getLoginCredentials() const = 0;
    virtual void showAuthenticationResult(bool success) const = 0;
    virtual void showAuthOptions() = 0;
    virtual int getAuthChoice() = 0;
    virtual std::tuple<std::string, std::string, std::string> getRegistrationData() = 0;
    virtual void showRegistrationResult(bool success, const std::string& errorMessage) = 0;
};

#endif //AUTHVIEW_H
