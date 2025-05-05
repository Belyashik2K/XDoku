//
// Created by Belyashik2K on 07.04.2025.
//

#ifndef POSTGRESQLSESSIONREPOSITORY_H
#define POSTGRESQLSESSIONREPOSITORY_H
#include "infrastructure/database/PostgreSQL/PostgreSQLDatabase.h"
#include "interfaces/database/repositories/ISessionRepository.h"

class PostgreSQLSessionRepository final : public ISessionRepository {
    std::shared_ptr<PostgreSQLDatabase> database;
public:
    explicit PostgreSQLSessionRepository(std::shared_ptr<PostgreSQLDatabase> database);

    bool createSession(const int &userId, const std::string &sessionId) const override;
    std::optional<std::pair<int, Timestamp>> getUserIdAndSessionExpiration(const std::string &sessionId) const override;
    std::optional<int> getUserIdBySessionId(const std::string &sessionId) const override;
    bool deleteSession(const std::string &sessionId) const override;
};

#endif //POSTGRESQLSESSIONREPOSITORY_H
