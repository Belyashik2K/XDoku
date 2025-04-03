//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef AUTHVIEW_H
#define AUTHVIEW_H
#include <string>

class IAuthView {
public:
    virtual ~IAuthView() = default;

    virtual void showWelcomeMessage() const = 0;
    virtual std::pair<std::string, std::string> getLoginCredentials() const = 0;
    virtual void showAuthenticationResult(bool success) const = 0;
};

#endif //AUTHVIEW_H
