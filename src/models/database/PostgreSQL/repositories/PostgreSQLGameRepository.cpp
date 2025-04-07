//
// Created by Belyashik2K on 07.04.2025.
//

#include "models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"

#include "models/database/PostgreSQL/PostgreSQLQuery.h"

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
    auto [fst, snd] = game.getGridsAsJson();
    query.addParameter(fst.dump());
    query.addParameter(snd.dump());
    query.addParameter(game.getDifficultyAsString());

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
    const bool exitedWhileSolved = row["exited_while_solved"].as<bool>();

    return SudokuGame::loadGame(
        id,
        userId,
        fst.dump(),
        snd.dump(),
        game.getDifficultyAsString(),
        mistakesCount,
        startTime,
        endTime,
        status,
        exitedWhileSolved
    );
}
