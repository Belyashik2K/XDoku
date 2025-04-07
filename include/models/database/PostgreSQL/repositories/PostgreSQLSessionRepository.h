//
// Created by Belyashik2K on 07.04.2025.
//

#ifndef POSTGRESQLSESSIONREPOSITORY_H
#define POSTGRESQLSESSIONREPOSITORY_H

#include "core/database/repositories/ISessionRepository.h"
#include "models/database/PostgreSQL/PostgreSQLDatabase.h"

class PostgreSQLSessionRepository final : public ISessionRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLSessionRepository(std::shared_ptr<PostgreSQLDatabase> database);

    bool createSession(const int &userId, const std::string &sessionId) const override;
    std::optional<std::string> getUsernameBySessionId(const std::string &sessionId) const override;
};

#endif //POSTGRESQLSESSIONREPOSITORY_H
