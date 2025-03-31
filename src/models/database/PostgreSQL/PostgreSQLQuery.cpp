//
// Created by Belyashik2K on 31.03.2025.
//

#include "../../../../include/models/database/PostgreSQL/PostgreSQLQuery.h"

PostgreSQLQuery::PostgreSQLQuery(const std::string &queryString) {
    this->queryString = queryString;
    this->queryParameters = pqxx::params();
}

std::string PostgreSQLQuery::getQueryString() const {
    return this->queryString;
}

pqxx::params PostgreSQLQuery::getQueryParameters() {
    return this->queryParameters;
}

void PostgreSQLQuery::addParameter(const std::string &parameter) {
    this->queryParameters.append(parameter);
}