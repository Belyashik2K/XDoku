//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H

#include <memory>
#include <string>

#include "core/database/IDatabase.h"


template <typename T, typename U, typename V>
class IUserRepository {
protected:
    std::shared_ptr<IDatabase<T, U, V>> database;
public:
    explicit IUserRepository(std::shared_ptr<IDatabase<T, U, V>> database) : database(std::move(database)) {}
    virtual ~IUserRepository() = default;

    virtual bool create(const std::string& username, const std::string &email, const std::string& password) = 0;
    virtual bool authenticate(const std::string& username, const std::string& password) = 0;
};

#endif //IUSERREPOSITORY_H
