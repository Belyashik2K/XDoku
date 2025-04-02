//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef POSTGRESQLQUERY_H
#define POSTGRESQLQUERY_H

#include <pqxx/pqxx>

#include "core/database/iQuery.h"

class PostgreSQLQuery : public IQuery<pqxx::params> {
    std::string queryString;
    pqxx::params queryParameters;

public:
    explicit PostgreSQLQuery(const std::string &queryString);
    ~PostgreSQLQuery() override = default;

    std::string getQueryString() const override;
    pqxx::params getQueryParameters() override;
    void addParameter(const std::string &parameter) override;
};

#endif //POSTGRESQLQUERY_H
