#include <iostream>
#include <bcrypt/BCrypt.hpp>

#include "models/User.h"
#include "models/database/PostgreSQL/repositories/UserRepository.h"

int main() {
    try {
        const std::string connectionString = "postgresql://xdoku_master:G3Jekh5xfyAuLXQqD8wY9n@xdoku.belyashik2k.ru:5432/xdoku";

        auto database = std::make_shared<PostgreSQLDatabase>(connectionString);
        bool isConnected = database->connect();
        if (!isConnected) {
            std::cerr << "Failed to connect to database!" << std::endl;
            return 1;
        }
        std::cout << "Connected to database!" << std::endl;

        const int userId = 1;
        std::string username = "Belyashik4K";
        std::string email = "b4k@belyashik2k.ru";
        std::string password = "a!K`Lg#4@';n*]^(jpfEqv";
        std::string passwordCopy = password;
        const std::string createdAt = "2025-03-31 00:00:00";

        const User user(userId, username, email, password, createdAt);

        PostgreSQLUserRepository userRepo(database);
        const bool result = userRepo.create(user.getUsername(), user.getEmail(), user.getPasswordHash());
        std::cout << "User with given data" << (result ? " created :)" : " not created :(") << std::endl;

        std::cout << "Trying to authenticate user..." << std::endl;

        try {
            const User authenticatedUser = userRepo.authenticate(user.getUsername(), user.getPasswordHash());
            std::cout << "User found, trying to match passwords..." << std::endl;
            const bool passwordsMatch = BCrypt::validatePassword(passwordCopy, authenticatedUser.getPasswordHash());
            if (!passwordsMatch) {
                std::cerr << "Passwords do not match!" << std::endl;
                return 1;
            }

            std::cout << "User authenticated!" << std::endl;
            std::cout << "User ID: " << authenticatedUser.getId() << std::endl;
            std::cout << "User created at: " << authenticatedUser.getCreatedAtAsString() << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Failed to authenticate user: " << e.what() << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
