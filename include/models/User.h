//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef USER_H
#define USER_H

#include <string>

#include <models/custom_types/Timestamp.h>

class User {
    const std::optional<int> id;
    std::string username;
    std::string email;
    std::string passwordHash;
    std::optional<int> rating;
    std::optional<Timestamp> createdAt;

public:
    User(
        std::optional<int> id,
        std::string username,
        std::string email,
        std::string password,
        std::optional<int> rating,
        const std::optional<std::string> &createdAt,
        bool needToHash
    );
    User(
        std::string username,
        std::string email,
        std::string password
    );
    ~User() = default;

    void setUsername(std::string username);
    void setEmail(std::string email);
    void setPasswordHash(std::string password, bool needToHash = true);
    void setRating(int rating);

    int getId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    std::string getPasswordHash() const;
    int getRating() const;
    Timestamp getCreatedAt() const;
    std::string getCreatedAtAsString() const;
    static bool validatePassword(const std::string& password); // TODO: Move to validator class
    static bool validateEmail(const std::string& email);
    static bool validateUsername(const std::string &username);
private:
    static std::string hashPassword(const std::string& password);
};

#endif //USER_H
