//
// Created by Belyashik2K on 02.04.2025.
//

#include <regex>
#include <cctype>

#include <models/User.h>
#include <models/custom_types/Timestamp.h>
#include <bcrypt/BCrypt.hpp>

User::User(
    int id,
    std::string &username,
    std::string &email,
    std::string &password,
    const std::string &createdAt
): id(id), createdAt(createdAt) {
    setUsername(std::move(username));
    setEmail(std::move(email));
    setPasswordHash(std::move(password));
}

std::string User::getEmail() const {
    return this->email;
}

int User::getId() const {
    return this->id;
}

std::string User::getUsername() const {
    return this->username;
}

std::string User::getPasswordHash() const {
    return this->passwordHash;
}

Timestamp User::getCreatedAt() const {
    return this->createdAt;
}

std::string User::getCreatedAtAsString() const {
    return this->createdAt.toString();
}

void User::setEmail(std::string email) {
    if (!validateEmail(email)) {
        throw std::invalid_argument("Invalid email");
    }
    this->email = std::move(email);
}

void User::setPasswordHash(std::string password) {
    if (!validatePassword(password)) {
        throw std::invalid_argument("Invalid password");
    }
    this->passwordHash = hashPassword(std::move(password));
}

void User::setUsername(std::string username) {
    if (!validateUsername(username)) {
        throw std::invalid_argument("Invalid username");
    }
    this->username = std::move(username);
}

bool User::validateEmail(const std::string &email) {
    const std::regex emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    return std::regex_match(email, emailRegex);
}

bool User::validatePassword(const std::string &password) {
    bool hasDigit = false;
    bool hasLower = false;
    bool hasUpper = false;
    bool hasSpecial = false;
    const bool lenGreaterOrEqual8 = password.length() >= 8;

    for (const char &c : password) {
        if (std::isdigit(c)) {
            hasDigit = true;
        } else if (std::islower(c)) {
            hasLower = true;
        } else if (std::isupper(c)) {
            hasUpper = true;
        } else if (std::ispunct(c)) {
            hasSpecial = true;
        }
    }

    return hasDigit && hasLower && hasUpper && hasSpecial && lenGreaterOrEqual8;
}

bool User::validateUsername(const std::string &username) {
    for (const char &c : username) {
        if (!std::isalnum(c) && c != '_') {
            return false;
        }
    }
    return true;
}

std::string User::hashPassword(const std::string &password) {
    std::string hash = BCrypt::generateHash(password);
    return hash;
}
