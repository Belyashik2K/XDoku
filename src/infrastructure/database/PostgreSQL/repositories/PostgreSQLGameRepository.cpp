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

std::optional<std::unique_ptr<SudokuGame>> PostgreSQLGameRepository::createGame(const int userId, std::unique_ptr<SudokuGame> game) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        INSERT INTO games (user_id, board, solution, difficulty)
        VALUES ($1, $2, $3, $4)
        RETURNING id, start_time, end_time, status
    )");
    query.addParameter(std::to_string(userId));
    nlohmann::json current = SudokuGridSerializer::saveGridToJson(game->getCurrentGrid());
    nlohmann::json solution = SudokuGridSerializer::saveGridToJson(game->getSolutionGrid());
    query.addParameter(current.dump());
    query.addParameter(solution.dump());
    query.addParameter(SudokuDifficulty::getDifficultyName(game->getDifficulty()));

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
    constexpr int mistakesCount = 0;
    const auto status = row["status"].as<std::string>();

    return SudokuGameLoader::loadGame(
        id,
        userId,
        current.dump(),
        solution.dump(),
        SudokuDifficulty::getDifficultyName(game->getDifficulty()),
        mistakesCount,
        startTime,
        endTime,
        status
    );
}

std::optional<std::unique_ptr<SudokuGame>> PostgreSQLGameRepository::getGame(int gameId) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT id, user_id, board, solution, difficulty,
               start_time, end_time, status
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
    constexpr int mistakesCount = 0;
    const auto startTime = row["start_time"].as<std::string>();

    std::optional<std::string> endTime;
    if (row["end_time"].is_null()) {
        endTime = std::nullopt;
    } else {
        endTime = row["end_time"].as<std::string>();
    }

    const auto status = row["status"].as<std::string>();

    return SudokuGameLoader::loadGame(
        id,
        userId,
        grid,
        solutionGrid,
        difficulty,
        mistakesCount,
        startTime,
        endTime,
        status,
        getMovesByGameId(id)
    );
}

std::optional<std::unique_ptr<SudokuGame>> PostgreSQLGameRepository::getUserCurrentGame(int userId) {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT id, user_id, board, solution, difficulty,
               start_time, end_time, status
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
    constexpr int mistakesCount = 0;
    const auto startTime = row["start_time"].as<std::string>();

    std::optional<std::string> endTime;
    if (row["end_time"].is_null()) {
        endTime = std::nullopt;
    } else {
        endTime = row["end_time"].as<std::string>();
    }

    const auto status = row["status"].as<std::string>();

    printf("[PostgreSQLGameRepository] Found game with ID: %d for user ID: %d\n", id, finalUserId);

    return SudokuGameLoader::loadGame(
        id,
        userId,
        grid,
        solutionGrid,
        difficulty,
        mistakesCount,
        startTime,
        endTime,
        status,
        getMovesByGameId(id)
    );
}

bool PostgreSQLGameRepository::updateGame(const int gameId, const SudokuGameStatusEnum status, const std::optional<Timestamp> &endTime) {
    if (!database->isConnected()) {
        return false;
    }
    PostgreSQLQuery query(R"(
        UPDATE games
        SET status = $1,
            end_time = $2
        WHERE id = $3
    )");
    query.addParameter(SudokuGameStatus::toString(status));
    if (endTime.has_value()) {
        query.addParameter(endTime.value().toString());
    } else {
        query.addParameter("");
    }
    query.addParameter(std::to_string(gameId));
    const pqxx::result result = database->execute(query);
    return result.affected_rows() > 0;
}

std::optional<std::vector<std::unique_ptr<SudokuMove>>> PostgreSQLGameRepository::getMovesByGameId(const int gameId) const {
    if (!database->isConnected()) {
        return std::nullopt;
    }

    PostgreSQLQuery query(R"(
        SELECT id, game_id, row, col, value, is_valid FROM moves
        WHERE game_id = $1
    )");
    query.addParameter(std::to_string(gameId));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return std::nullopt;
    }
    std::vector<std::unique_ptr<SudokuMove>> moves;
    for (const auto &row: result) {
        const int id = row["id"].as<int>();
        const int gridRow = row["row"].as<int>();
        const int gridCol = row["col"].as<int>();
        const int value = row["value"].as<int>();
        const bool isValid = row["is_valid"].as<bool>();

        moves.emplace_back(std::make_unique<SudokuMove>(id, gameId, gridRow, gridCol, value, isValid));
    }

    return moves;
}
