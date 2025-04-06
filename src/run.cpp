#include <iostream>
#include <ncurses.h>
#include <bcrypt/BCrypt.hpp>

#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "presenters/AuthPresenter.h"
#include "views/auth/ConsoleAuthView.h"

#include "tests/imgui/load.h"
#include "tests/sudoku/generator.h"

int main() {

    initscr();

    // testLoadImgui();
    // testSudokuGenerator();

    try {
        const std::string connectionString = "postgresql://xdoku_master:G3Jekh5xfyAuLXQqD8wY9n@xdoku.belyashik2k.ru:5432/xdoku";

        auto database = std::make_shared<PostgreSQLDatabase>(connectionString);
        const auto userRepository = std::make_shared<PostgreSQLUserRepository>(database);
        const auto authView = std::make_shared<ConsoleAuthView>();

        const AuthPresenter authPresenter(userRepository, authView);
        authPresenter.run();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
