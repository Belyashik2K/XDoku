#include <iostream>
#include <ncurses.h>
#include <bcrypt/BCrypt.hpp>

#include "models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"
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
        const PostgreSQLRatingRepository ratingRepository(database);
        PostgreSQLMoveRepository moveRepository(database);
        PostgreSQLGameRepository gameRepository(database);

        const auto authView = std::make_shared<ConsoleAuthView>();

        const AuthPresenter authPresenter(userRepository, sessionRepository, authView);
        authPresenter.run();

        // constexpr int userId = 61;
        // auto ratingChange = -10;
        // const auto comment = std::format("Testing add rating ({} points)", ratingChange);
        // std::cout << comment << std::endl;
        // ratingRepository.createRatingHistoryRecord(userId, std::nullopt, ratingChange, comment);
        // std::cout << "Rating added successfully!" << std::endl;

        std::optional<std::vector<LeaderboardPlace>> leaderboard = ratingRepository.getLeaderboard(10);
        if (leaderboard.has_value()) {
            std::cout << "Leaderboard:" << std::endl;
            for (const auto &place: leaderboard.value()) {
                place.printInfo();
            }
        } else {
            std::cout << "Failed to retrieve leaderboard." << std::endl;
        }

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
        //
        // std::optional<SudokuGame> loadedGame = gameRepository.getGame(19);
        // if (loadedGame.has_value()) {
        //     std::cout << "Game loaded successfully!" << std::endl;
        //     std::optional<std::vector<SudokuMove>> moves = moveRepository.getMovesByGameId(19);
        //     std::cout << "Moves loaded successfully!" << std::endl;
        //
        //     for (const auto &move: moves.value()) {
        //         // std::cout << "Move: " << move.getValue() << " at (" << move.coords().first << ", " << move.coords().second << ")" << std::endl;
        //         loadedGame.value().addMove(move);
        //     }
        //
        //     loadedGame.value().printInfo();
        // } else {
        //     std::cout << "Failed to load game." << std::endl;
        // }
        //
        // SudokuMove move(19, 8, 6, 8, true);
        // bool isMoveCreated = moveRepository.createMove(move);
        // std::cout << "Move created: " << (isMoveCreated ? "true" : "false") << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
