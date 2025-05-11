//
// Created by belyashik2k on 5/11/25.
//

#ifndef POSTGRESQLREPOSITORYFACTORY_H
#define POSTGRESQLREPOSITORYFACTORY_H
#include "infrastructure/database/PostgreSQL/PostgreSQLDatabase.h"
#include "interfaces/database/repositories/IRepositoryFactory.h"

class PostgreSQLRepositoryFactory final : public IRepositoryFactory {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLRepositoryFactory(const std::string &database_url);

    std::shared_ptr<IGameRepository> createGameRepository() override;
    std::shared_ptr<IMoveRepository> createMoveRepository() override;
    std::shared_ptr<IRatingRepository> createRatingRepository() override;
    std::shared_ptr<ISessionRepository> createSessionRepository() override;
    std::shared_ptr<IUserRepository> createUserRepository() override;
};

#endif //POSTGRESQLREPOSITORYFACTORY_H
