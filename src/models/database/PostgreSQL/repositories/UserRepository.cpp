//
// Created by Belyashik2K on 31.03.2025.
//

#include "../../../../include/models/database/PostgreSQL/repositories/UserRepository.h"

#include "../../../../../include/models/database/PostgreSQL/PostgreSQLQuery.h"

bool PostgreSQLUserRepository::create(
    const std::string &username,
    const std::string &email,
    const std::string &password
) {
    if (!database->isConnected()) {
        return false;
    }

    try {
        PostgreSQLQuery query("INSERT INTO users (username, email, password_hash) VALUES ($1, $2, $3)");
        query.addParameter(username);
        query.addParameter(email);
        query.addParameter(password);

        database->execute(query);
        return true;
    } catch (const std::exception &e) {
        return false;
    }
}

bool PostgreSQLUserRepository::authenticate(const std::string &username, const std::string &password) {
    if (!database->isConnected()) {
        return false;
    }
    return true;
}
