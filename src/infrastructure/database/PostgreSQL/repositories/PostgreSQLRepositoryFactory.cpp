//
// Created by belyashik2k on 5/11/25.
//

#include "infrastructure/database/PostgreSQL/factories/PostgreSQLRepositoryFactory.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLGameRepository.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h"
#include "infrastructure/database/PostgreSQL/repositories/PostgreSQLUserRepository.h"

PostgreSQLRepositoryFactory::PostgreSQLRepositoryFactory(const std::string &database_url) {
    database = std::make_shared<PostgreSQLDatabase>(database_url);
}

std::shared_ptr<IGameRepository> PostgreSQLRepositoryFactory::createGameRepository() {
    return std::make_shared<PostgreSQLGameRepository>(database);
}

std::shared_ptr<IMoveRepository> PostgreSQLRepositoryFactory::createMoveRepository() {
    return std::make_shared<PostgreSQLMoveRepository>(database);
}

std::shared_ptr<IRatingRepository> PostgreSQLRepositoryFactory::createRatingRepository() {
    return std::make_shared<PostgreSQLRatingRepository>(database);
}

std::shared_ptr<ISessionRepository> PostgreSQLRepositoryFactory::createSessionRepository() {
    return std::make_shared<PostgreSQLSessionRepository>(database);
}

std::shared_ptr<IUserRepository> PostgreSQLRepositoryFactory::createUserRepository() {
    return std::make_shared<PostgreSQLUserRepository>(database);
}




