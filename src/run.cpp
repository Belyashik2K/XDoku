#include <iostream>

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

        PostgreSQLUserRepository userRepo(database);
        const bool result = userRepo.create("belyashik2k2", "test@belyashik3k.ru", "test2");
        std::cout << "User with given data" << (result ? " created :)" : " not created :(") << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
