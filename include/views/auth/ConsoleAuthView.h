//
// Created by Belyashik2K on 03.04.2025.
//

#ifndef CONSOLEAUTHVIEW_H
#define CONSOLEAUTHVIEW_H

#include "IAuthView.h"


class ConsoleAuthView : public IAuthView {
public:
    ~ConsoleAuthView() override = default;

    void showWelcomeMessage() const override;
    std::pair<std::string, std::string> getLoginCredentials() const override;
    void showAuthenticationResult(bool success) const override;
};

#endif //CONSOLEAUTHVIEW_H
