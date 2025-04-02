#include "models/database/PostgreSQL/repositories/UserRepository.h"

#include <iostream>

#include "models/database/PostgreSQL/PostgreSQLQuery.h"

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

        const pqxx::result result = database->execute(query);
        return result.affected_rows() > 0;
    } catch (const std::exception &e) {
        std::cout << "PostgreSQLUserRepository::create(): " << e.what() << std::endl;
        return false;
    }
}

bool PostgreSQLUserRepository::authenticate(const std::string &username, const std::string &password) {
    if (!database->isConnected()) {
        return false;
    }
    return true;
}
