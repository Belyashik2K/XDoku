//
// Created by Belyashik2K on 31.03.2025.
//

#include "../../../../include/models/database/PostgreSQL/repositories/UserRepository.h"

bool PostgreSQLUserRepository::create(const std::string &username, const std::string &password) {
    if (!database->isConnected()) {
        return false;
    }
    return true;
}

bool PostgreSQLUserRepository::authenticate(const std::string &username, const std::string &password) {
    if (!database->isConnected()) {
        return false;
    }
    return true;
}

