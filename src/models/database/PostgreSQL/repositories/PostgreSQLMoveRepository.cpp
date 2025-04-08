//
// Created by belyashik2k on 4/8/25.
//

#include "models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"

PostgreSQLMoveRepository::PostgreSQLMoveRepository(std::shared_ptr<PostgreSQLDatabase> database) {
    this->database = std::move(database);
}


bool PostgreSQLMoveRepository::createMove(int gameId, int userId, SudokuCell move) {
    return true;
}
