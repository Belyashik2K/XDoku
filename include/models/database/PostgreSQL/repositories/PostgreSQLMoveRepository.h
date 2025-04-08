//
// Created by belyashik2k on 4/8/25.
//

#ifndef POSTGRESQLMOVEREPOSITORY_H
#define POSTGRESQLMOVEREPOSITORY_H
#include "core/database/repositories/IMoveRepository.h"
#include "models/database/PostgreSQL/PostgreSQLDatabase.h"
#include "models/sudoku/SudokuMove.h"

class PostgreSQLMoveRepository final : public IMoveRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLMoveRepository(std::shared_ptr<PostgreSQLDatabase> database);

    bool createMove(SudokuMove move) override;
    std::optional<std::vector<SudokuMove>> getMovesByGameId(int gameId) override;
};

#endif //POSTGRESQLMOVEREPOSITORY_H
