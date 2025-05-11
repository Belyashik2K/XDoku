//
// Created by belyashik2k on 5/11/25.
//

#ifndef IREPOSITROYFACTORY_H
#define IREPOSITROYFACTORY_H

#include <memory>

#include "IUserRepository.h"
#include "ISessionRepository.h"
#include "IRatingRepository.h"
#include "IGameRepository.h"
#include "IMoveRepository.h"

class IRepositoryFactory {
public:
    virtual std::shared_ptr<IUserRepository> createUserRepository() = 0;
    virtual std::shared_ptr<ISessionRepository> createSessionRepository() = 0;
    virtual std::shared_ptr<IRatingRepository> createRatingRepository() = 0;
    virtual std::shared_ptr<IGameRepository> createGameRepository() = 0;
    virtual std::shared_ptr<IMoveRepository> createMoveRepository() = 0;

    virtual ~IRepositoryFactory() = default;
};

#endif //IREPOSITROYFACTORY_H
