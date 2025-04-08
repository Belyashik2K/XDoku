#include <iostream>
#include <ncurses.h>
#include <bcrypt/BCrypt.hpp>

#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "presenters/AuthPresenter.h"
#include "views/auth/ConsoleAuthView.h"

#include "tests/imgui/load.h"
#include "tests/sudoku/generator.h"

int main() {

    initscr();

    // testLoadImgui();
    // testSudokuGameGenerator();

    try {
        const std::string connectionString = "postgresql://xdoku_master:G3Jekh5xfyAuLXQqD8wY9n@xdoku.belyashik2k.ru:5432/xdoku";

        auto database = std::make_shared<PostgreSQLDatabase>(connectionString);
        const auto userRepository = std::make_shared<PostgreSQLUserRepository>(database);
        const auto sessionRepository = std::make_shared<PostgreSQLSessionRepository>(database);
        const auto authView = std::make_shared<ConsoleAuthView>();

        const AuthPresenter authPresenter(userRepository, sessionRepository, authView);
        authPresenter.run();

        // const PostgreSQLRatingRepository ratingRepository(database);
        // constexpr int userId = 61;
        // auto ratingChange = -10;
        // const auto comment = std::format("Testing add rating ({} points)", ratingChange);
        // std::cout << comment << std::endl;
        // ratingRepository.createRatingHistoryRecord(userId, std::nullopt, ratingChange, comment);
        // std::cout << "Rating added successfully!" << std::endl;

        // std::optional<std::vector<LeaderboardPlace>> leaderboard = ratingRepository.getLeaderboard(10);
        // if (leaderboard.has_value()) {
        //     std::cout << "Leaderboard:" << std::endl;
        //     for (const auto &place: leaderboard.value()) {
        //         place.printInfo();
        //     }
        // } else {
        //     std::cout << "Failed to retrieve leaderboard." << std::endl;
        // }

        // const SudokuGame game = SudokuGame::startNewGame(69, SudokuDifficultyEnum::EXPERT);
        // game.printInfo();
        // std::cout << "Trying to save game..." << std::endl;
        // PostgreSQLGameRepository gameRepository(database);
        // const auto savedGame = gameRepository.createGame(69, game);
        // if (savedGame.has_value()) {
        //     std::cout << "Game saved successfully!" << std::endl;
        //     savedGame.value().printInfo();
        // } else {
        //     std::cout << "Failed to save game." << std::endl;
        // }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
