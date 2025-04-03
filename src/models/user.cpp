//
// Created by Belyashik2K on 02.04.2025.
//

#include <regex>
#include <cctype>
#include <iostream>
#include <utility>
#include <bcrypt/BCrypt.hpp>

#include <models/User.h>
#include <models/custom_types/Timestamp.h>

User::User(
    const std::optional<int> id,
    std::string username,
    std::string email,
    std::string password,
    const std::optional<int> rating,
    const std::optional<std::string> &createdAt,
    const bool needToHash
): id(id), rating(rating), createdAt(createdAt) {
    setUsername(std::move(username));
    setEmail(std::move(email));
    setPasswordHash(std::move(password), needToHash);
}

User::User(
    std::string username,
    std::string email,
    std::string password
): User(std::nullopt, std::move(username), std::move(email), std::move(password), std::nullopt, std::nullopt) {
}

std::string User::getEmail() const {
    return this->email;
}

int User::getId() const {
    if (!this->id.has_value()) {
        throw std::runtime_error("User ID is not set");
    }
    return this->id.value();
}

std::string User::getUsername() const {
    return this->username;
}

std::string User::getPasswordHash() const {
    return this->passwordHash;
}

Timestamp User::getCreatedAt() const {
    if (!this->createdAt.has_value()) {
        throw std::runtime_error("CreatedAt is not set");
    }
    return this->createdAt.value();
}

std::string User::getCreatedAtAsString() const {
    if (!this->createdAt.has_value()) {
        throw std::runtime_error("CreatedAt is not set");
    }
    return this->createdAt.value().toString();
}

void User::setEmail(std::string email) {
    if (!validateEmail(email)) {
        throw std::invalid_argument("Invalid email");
    }
    this->email = std::move(email);
}

void User::setPasswordHash(std::string password, const bool needToHash) {
    if (!validatePassword(password)) {
        throw std::invalid_argument("Invalid password");
    }

    if (!needToHash) {
        this->passwordHash = std::move(password);
        return;
    }
    this->passwordHash = hashPassword(password);
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

    for (const char &c: password) {
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
    for (const char &c: username) {
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

void User::setRating(int rating) {
    if (rating < 0) {
        throw std::invalid_argument("Rating cannot be negative");
    }
    this->rating = rating;
}

int User::getRating() const {
    if (!this->rating.has_value()) {
        throw std::runtime_error("Rating is not set");
    }
    return this->rating.value();
}
