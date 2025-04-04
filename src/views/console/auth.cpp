//
// Created by Belyashik2K on 03.04.2025.
//

#include <iostream>

#include "views/auth/ConsoleAuthView.h"

void ConsoleAuthView::render() const {
    ;
}

void ConsoleAuthView::showText(const std::string &text) const {
    std::cout << text << std::endl;
}


void ConsoleAuthView::clearScreen() const {
    ;
}

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

void ConsoleAuthView::showAuthOptions() {
    std::cout << "Authentication System\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "Enter your choice (1 or 2): ";
}

int ConsoleAuthView::getAuthChoice() {
    int choice;
    std::cin >> choice;

    while (choice != 1 && choice != 2) {
        std::cout << "Invalid choice. Please enter 1 or 2: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> choice;
    }

    return choice;
}

std::tuple<std::string, std::string, std::string> ConsoleAuthView::getRegistrationData() {
    std::string username, email, password, confirmPassword;

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter email: ";
    std::cin >> email;

    std::cout << "Enter password: ";
    std::cin >> password;

    std::cout << "Confirm password: ";
    std::cin >> confirmPassword;

    while (password != confirmPassword) {
        std::cout << "Passwords do not match. Please try again.\n";
        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "Confirm password: ";
        std::cin >> confirmPassword;
    }

    return {username, email, password};
}

void ConsoleAuthView::showRegistrationResult(bool success, const std::string &errorMessage) {
    if (success) {
        std::cout << "Registration successful!\n";
    } else {
        std::cout << "Registration failed: " << errorMessage << std::endl;
    }
}
