//
// Created by Belyashik2K on 07.04.2025.
//

#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"

#include "domain/sudoku/utils/SudokuLoader.h"
#include "domain/sudoku/utils/SudokuSerializer.h"
#include "infrastructure/database/PostgreSQL/PostgreSQLQuery.h"

PostgreSQLGameRepository::PostgreSQLGameRepository(std::shared_ptr<PostgreSQLDatabase> database) {
    this->database = std::move(database);
}

std::optional<SudokuGame> PostgreSQLGameRepository::createGame(const int userId, SudokuGame game) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        INSERT INTO games (user_id, board, solution, difficulty)
        VALUES ($1, $2, $3, $4)
        RETURNING id, start_time, end_time, mistakes_count, status, exited_while_solved
    )");
    query.addParameter(std::to_string(userId));
    nlohmann::json current = SudokuGridSerializer::saveGridToJson(game.getCurrentGrid());
    nlohmann::json solution = SudokuGridSerializer::saveGridToJson(game.getSolutionGrid());
    query.addParameter(current.dump());
    query.addParameter(solution.dump());
    query.addParameter(SudokuDifficulty::getDifficultyName(game.getDifficulty()));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }
    const auto row = result[0];
    const int id = row["id"].as<int>();
    const auto startTime = row["start_time"].as<std::string>();

    std::optional<std::string> endTime;
    if (row["end_time"].is_null()) {
        endTime = std::nullopt;
    } else {
        endTime = row["end_time"].as<std::string>();
    }
    const int mistakesCount = row["mistakes_count"].as<int>();
    const auto status = row["status"].as<std::string>();
    // const bool exitedWhileSolved = row["exited_while_solved"].as<bool>();

    return SudokuGameLoader::loadGame(
        id,
        userId,
        current.dump(),
        solution.dump(),
        SudokuDifficulty::getDifficultyName(game.getDifficulty()),
        mistakesCount,
        startTime,
        endTime,
        status
    );
}

std::optional<SudokuGame> PostgreSQLGameRepository::getGame(int gameId) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT id, user_id, board, solution, difficulty, mistakes_count,
               start_time, end_time, status, exited_while_solved
        FROM games
        WHERE id = $1
    )");
    query.addParameter(std::to_string(gameId));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }

    pqxx::row row = result[0];
    const int id = row["id"].as<int>();
    const int userId = row["user_id"].as<int>();
    const auto grid = row["board"].as<std::string>();
    const auto solutionGrid = row["solution"].as<std::string>();
    const auto difficulty = row["difficulty"].as<std::string>();
    const int mistakesCount = row["mistakes_count"].as<int>();
    const auto startTime = row["start_time"].as<std::string>();

    std::optional<std::string> endTime;
    if (row["end_time"].is_null()) {
        endTime = std::nullopt;
    } else {
        endTime = row["end_time"].as<std::string>();
    }

    const auto status = row["status"].as<std::string>();
    // const bool exitedWhileSolved = row["exited_while_solved"].as<bool>();

    return SudokuGameLoader::loadGame(
        id,
        userId,
        grid,
        solutionGrid,
        difficulty,
        mistakesCount,
        startTime,
        endTime,
        status
    );
}

std::optional<SudokuGame> PostgreSQLGameRepository::getUserCurrentGame(int userId) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT id, user_id, board, solution, difficulty, mistakes_count,
               start_time, end_time, status, exited_while_solved
        FROM games
        WHERE user_id = $1
        AND status = $2
    )");
    query.addParameter(std::to_string(userId));
    query.addParameter(SudokuGameStatus::toString(SudokuGameStatusEnum::IN_PROGRESS));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }

    pqxx::row row = result[0];
    const int id = row["id"].as<int>();
    const int finalUserId = row["user_id"].as<int>();
    const auto grid = row["board"].as<std::string>();
    const auto solutionGrid = row["solution"].as<std::string>();
    const auto difficulty = row["difficulty"].as<std::string>();
    const int mistakesCount = row["mistakes_count"].as<int>();
    const auto startTime = row["start_time"].as<std::string>();

    std::optional<std::string> endTime;
    if (row["end_time"].is_null()) {
        endTime = std::nullopt;
    } else {
        endTime = row["end_time"].as<std::string>();
    }

    const auto status = row["status"].as<std::string>();
    // const bool exitedWhileSolved = row["exited_while_solved"].as<bool>();

    return SudokuGameLoader::loadGame(
        id,
        userId,
        grid,
        solutionGrid,
        difficulty,
        mistakesCount,
        startTime,
        endTime,
        status
    );
}