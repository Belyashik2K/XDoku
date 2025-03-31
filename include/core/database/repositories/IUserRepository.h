//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H

#include <memory>
#include <string>

#include "../IDatabase.h"

template <typename T, typename U>
class IUserRepository {
protected:
    std::shared_ptr<IDatabase<T, U>> database;
public:
    explicit IUserRepository(std::shared_ptr<IDatabase<T, U>> database) : database(std::move(database)) {}
    virtual ~IUserRepository() = default;

    virtual bool create(const std::string& username, const std::string &email, const std::string& password) = 0;
    virtual bool authenticate(const std::string& username, const std::string& password) = 0;
};

#endif //IUSERREPOSITORY_H
