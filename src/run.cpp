#include <iostream>

#include "../include/models/database/PostgreSQL/PostgreSQLDatabase.h"
#include "../include/models/database/PostgreSQL/repositories/UserRepository.h"

int main() {
    try {
        const std::string connectionString =
                "";
        auto database = std::make_shared<PostgreSQLDatabase>(connectionString);
        bool isConnected = database->connect();
        if (!isConnected) {
            std::cerr << "Failed to connect to database!" << std::endl;
            return 1;
        }
        std::cout << "Connected to database!" << std::endl;
        PostgreSQLUserRepository userRepo(database);
        const bool result = userRepo.create("belyashik2k", "test");
        std::cout << "Result of operation create is " << result << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
