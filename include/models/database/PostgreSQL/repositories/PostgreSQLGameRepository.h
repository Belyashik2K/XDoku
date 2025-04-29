//
// Created by Belyashik2K on 07.04.2025.
//

#ifndef POSTGRESQLGAMEREPOSITORY_H
#define POSTGRESQLGAMEREPOSITORY_H

#include "core/database/repositories/IGameRepository.h"
#include "models/database/PostgreSQL/PostgreSQLDatabase.h"

class PostgreSQLGameRepository final : public IGameRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLGameRepository(std::shared_ptr<PostgreSQLDatabase> database);
    std::optional<SudokuGame> createGame(
        int userId,
        SudokuGame game
    ) override;
    std::optional<SudokuGame> getGame(int gameId) override;

};

#endif //POSTGRESQLGAMEREPOSITORY_H
