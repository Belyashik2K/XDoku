//
// Created by belyashik2k on 4/8/25.
//
#include <iostream>

#include "infrastructure/database/PostgreSQL/PostgreSQLQuery.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

PostgreSQLMoveRepository::PostgreSQLMoveRepository(std::shared_ptr<PostgreSQLDatabase> database) {
    this->database = std::move(database);
}


bool PostgreSQLMoveRepository::createMove(const std::unique_ptr<SudokuMove>& move) {
    if (!database->isConnected()) {
        return false;
    }
    PostgreSQLQuery query(R"(
        INSERT INTO moves (game_id, row, col, value, is_valid)
        VALUES ($1, $2, $3, $4, $5)
        RETURNING id
    )");
    query.addParameter(std::to_string(move->getGameId()));
    query.addParameter(std::to_string(move->coords().first));
    query.addParameter(std::to_string(move->coords().second));
    query.addParameter(std::to_string(move->getValue()));
    query.addParameter(std::to_string(move->isValidMove()));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return false;
    }
    return true;
}

bool PostgreSQLMoveRepository::createMoves(const std::vector<std::unique_ptr<SudokuMove>> &moves) {
    if (moves.empty()) {
        return true;
    }
    if (!database->isConnected()) {
        return false;
    }

    std::string values;
    values.reserve(moves.size() * 32);
    int paramIndex = 1;
    for (std::size_t i = 0; i < moves.size(); ++i) {
        values += "($" + std::to_string(paramIndex++) + ", $" + std::to_string(paramIndex++) + ", $" +
                  std::to_string(paramIndex++) + ", $" + std::to_string(paramIndex++) + ", $" +
                  std::to_string(paramIndex++) + ")";
        if (i + 1 != moves.size()) {
            values += ", ";
        }
    }

    const std::string queryText =
        "INSERT INTO moves (game_id, row, col, value, is_valid) VALUES " + values + " RETURNING id";

    PostgreSQLQuery query(queryText);
    for (const auto &move : moves) {
        query.addParameter(std::to_string(move->isValidMove()));
        query.addParameter(std::to_string(move->getValue()));
        query.addParameter(std::to_string(move->coords().second));
        query.addParameter(std::to_string(move->coords().first));
        query.addParameter(std::to_string(move->getGameId()));

    }

    const pqxx::result result = database->execute(query);
    return !result.empty();
}

// std::optional<std::vector<SudokuMove>> PostgreSQLMoveRepository::getMovesByGameId(const int gameId) {
//     if (!database->isConnected()) {
//         return std::nullopt;
//     }
//
//     PostgreSQLQuery query(R"(
//         SELECT id, game_id, row, col, value, is_valid FROM moves
//         WHERE game_id = $1
//     )");
//     query.addParameter(std::to_string(gameId));
//
//     const pqxx::result result = database->execute(query);
//     if (result.empty()) {
//         return std::nullopt;
//     }
//     std::vector<SudokuMove> moves;
//     for (const auto &row: result) {
//         const int id = row["id"].as<int>();
//         const int gridRow = row["row"].as<int>();
//         const int gridCol = row["col"].as<int>();
//         const int value = row["value"].as<int>();
//         const bool isValid = row["is_valid"].as<bool>();
//
//         moves.emplace_back(id, gameId, gridRow, gridCol, value, isValid);
//     }
//
//     return moves;
// }
