//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H

#include <memory>
#include <string>

#include "core/database/IDatabase.h"
#include "models/User.h"


template <typename Connection, typename Params, typename Result>
class IUserRepository {
protected:
    std::shared_ptr<IDatabase<Connection, Params, Result>> database;
public:
    explicit IUserRepository(std::shared_ptr<IDatabase<Connection, Params, Result>> database) : database(std::move(database)) {}
    virtual ~IUserRepository() = default;

    virtual bool create(const std::string& username, const std::string &email, const std::string& password) = 0;
    virtual User get(const std::string& username) const = 0;
    virtual std::string getHashedPassword(const std::string &username) const = 0;
};

#endif //IUSERREPOSITORY_H
