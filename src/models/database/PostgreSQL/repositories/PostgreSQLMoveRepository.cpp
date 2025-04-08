//
// Created by belyashik2k on 4/8/25.
//

#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

#include "models/database/PostgreSQL/PostgreSQLQuery.h"
#include "models/sudoku/SudokuMove.h"

PostgreSQLMoveRepository::PostgreSQLMoveRepository(std::shared_ptr<PostgreSQLDatabase> database) {
    this->database = std::move(database);
}


bool PostgreSQLMoveRepository::createMove(const SudokuMove move) {
    if (!database->isConnected()) {
        return false;
    }
    PostgreSQLQuery query(R"(
        INSERT INTO moves (game_id, row, col, value, is_valid)
        VALUES ($1, $2, $3, $4, $5)
    )");
    query.addParameter(std::to_string(move.getGameId()));
    query.addParameter(std::to_string(move.coords().first));
    query.addParameter(std::to_string(move.coords().second));
    query.addParameter(std::to_string(move.getValue()));
    query.addParameter(std::to_string(move.isValidMove()));

    const pqxx::result result = database->execute(query);
    if (result.empty()) {
        return false;
    }
    return true;
}
