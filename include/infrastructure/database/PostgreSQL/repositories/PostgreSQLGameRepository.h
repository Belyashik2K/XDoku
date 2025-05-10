//
// Created by Belyashik2K on 07.04.2025.
//

#ifndef POSTGRESQLGAMEREPOSITORY_H
#define POSTGRESQLGAMEREPOSITORY_H

#include "infrastructure/database/PostgreSQL/PostgreSQLDatabase.h"
#include "interfaces/database/repositories/IGameRepository.h"

class PostgreSQLGameRepository final : public IGameRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLGameRepository(std::shared_ptr<PostgreSQLDatabase> database);
    std::optional<SudokuGame> createGame(
        int userId,
        SudokuGame game
    ) override;
    std::optional<SudokuGame> getGame(int gameId) override;
    std::optional<SudokuGame> getUserCurrentGame(int userId) override;
    bool updateGame(int gameId, SudokuGameStatusEnum status, const std::optional<Timestamp> &endTime) override;
};

#endif //POSTGRESQLGAMEREPOSITORY_H
