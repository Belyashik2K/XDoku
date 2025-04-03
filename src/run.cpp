#include <iostream>
#include <bcrypt/BCrypt.hpp>

#include "models/User.h"
#include "models/database/PostgreSQL/repositories/UserRepository.h"
#include "presenters/AuthPresenter.h"
#include "views/auth/ConsoleAuthView.h"

int main() {

    try {
        const std::string connectionString = "postgresql://xdoku_master:G3Jekh5xfyAuLXQqD8wY9n@xdoku.belyashik2k.ru:5432/xdoku";

        auto database = std::make_shared<PostgreSQLDatabase>(connectionString);
        const auto userRepository = std::make_shared<PostgreSQLUserRepository>(database);

        // User testUser("TestUser", "test@belyashik2k.ru", "Fb?yd0#StuCTz9a[");
        // userRepository->create(testUser.getUsername(), testUser.getEmail(), testUser.getPasswordHash());

        const auto authView = std::make_shared<ConsoleAuthView>();

        AuthPresenter<pqxx::connection, pqxx::params, pqxx::result> authPresenter(userRepository, authView);
        std::optional<User> user = authPresenter.authenticateUser();

        if (user) {
            std::cout << "Authenticated user rating: " << user->getRating() << std::endl;
        } else {
            std::cout << "Authentication failed." << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
