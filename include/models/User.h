//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef USER_H
#define USER_H

#include <string>

#include <models/custom_types/Timestamp.h>

class User {
    const int id;
    std::string username;
    std::string email;
    std::string passwordHash;
    Timestamp createdAt;

public:
    User(
        int id,
        std::string &username,
        std::string &email,
        std::string &password,
        const std::string &createdAt
    );
    ~User() = default;

    void setUsername(std::string username);
    void setEmail(std::string email);
    void setPasswordHash(std::string password);

    int getId() const;
    std::string getUsername() const;
    std::string getEmail() const;
    std::string getPasswordHash() const;
    Timestamp getCreatedAt() const;
    std::string getCreatedAtAsString() const;
private:
    static bool validatePassword(const std::string& password);
    static std::string hashPassword(const std::string& password);
    static bool validateEmail(const std::string& email);
    static bool validateUsername(const std::string &username);
};

#endif //USER_H
