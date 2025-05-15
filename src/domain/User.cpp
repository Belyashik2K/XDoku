//
// Created by Belyashik2K on 02.04.2025.
//

#include "domain/User.h"

#include <regex>
#include <cctype>
#include <iostream>
#include <utility>
#include <bcrypt/BCrypt.hpp>

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
): User(std::nullopt, std::move(username), std::move(email), std::move(password), std::nullopt, std::nullopt , true) {
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
    this->email = std::move(email);
}

void User::setPasswordHash(std::string password, const bool needToHash) {
    if (!needToHash) {
        this->passwordHash = std::move(password);
        return;
    }
    this->passwordHash = hashPassword(password);
}

void User::setUsername(std::string username) {
    this->username = std::move(username);
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