//
// Created by belyashik2k on 4/8/25.
//

#ifndef POSTGRESQLMOVEREPOSITORY_H
#define POSTGRESQLMOVEREPOSITORY_H
#include "infrastructure/database/PostgreSQL/PostgreSQLDatabase.h"
#include "interfaces/database/repositories/IMoveRepository.h"

class PostgreSQLMoveRepository final : public IMoveRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLMoveRepository(std::shared_ptr<PostgreSQLDatabase> database);

    bool createMove(SudokuMove move) override;
    std::optional<std::vector<SudokuMove>> getMovesByGameId(int gameId) override;
};

#endif //POSTGRESQLMOVEREPOSITORY_H
