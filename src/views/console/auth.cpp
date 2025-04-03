//
// Created by Belyashik2K on 03.04.2025.
//

#include <iostream>

#include "views/auth/ConsoleAuthView.h"

void ConsoleAuthView::showWelcomeMessage() const {
    std::cout << "Welcome to the Authentication System!\n";
}

std::pair<std::string, std::string> ConsoleAuthView::getLoginCredentials() const {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    return {username, password};
}

void ConsoleAuthView::showAuthenticationResult(bool success) const {
    if (success) {
        std::cout << "Authentication successful!\n";
    } else {
        std::cout << "Authentication failed.\n";
    }
}




