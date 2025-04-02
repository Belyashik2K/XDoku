#include <iostream>

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
        std::string username = "ilybnn";
        std::string email = "ilybnn@belyashik2k.ru";
        std::string password = "a!K`Lg#4@';n*]^(jpfEqv";
        const std::string createdAt = "2025-03-31 00:00:00";

        const User user(userId, username, email, password, createdAt);

        PostgreSQLUserRepository userRepo(database);
        const bool result = userRepo.create(user.getUsername(), user.getEmail(), user.getPasswordHash());
        std::cout << "User with given data" << (result ? " created :)" : " not created :(") << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
