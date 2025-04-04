//
// Created by Belyashik2K on 03.04.2025.
//

#ifndef CONSOLEAUTHVIEW_H
#define CONSOLEAUTHVIEW_H

#include "IAuthView.h"


class ConsoleAuthView : public IAuthView {
public:
    ~ConsoleAuthView() override = default;

    void render() const override;
    void showText(const std::string& text) const override;
    void clearScreen() const override;
    void showWelcomeMessage() const override;
    std::pair<std::string, std::string> getLoginCredentials() const override;
    void showAuthenticationResult(bool success) const override;
    void showAuthOptions() override;
    int getAuthChoice() override;
    std::tuple<std::string, std::string, std::string> getRegistrationData() override;
    void showRegistrationResult(bool success, const std::string& errorMessage) override;
};

#endif //CONSOLEAUTHVIEW_H
