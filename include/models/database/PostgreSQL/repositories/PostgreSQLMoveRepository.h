//
// Created by belyashik2k on 4/8/25.
//

#ifndef POSTGRESQLMOVEREPOSITORY_H
#define POSTGRESQLMOVEREPOSITORY_H
#include "core/database/repositories/IMoveRepository.h"
#include "models/database/PostgreSQL/PostgreSQLDatabase.h"

class PostgreSQLMoveRepository final : IMoveRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLMoveRepository(std::shared_ptr<PostgreSQLDatabase> database);
    bool createMove(int gameId, int userId, SudokuCell move) override;
};

#endif //POSTGRESQLMOVEREPOSITORY_H
