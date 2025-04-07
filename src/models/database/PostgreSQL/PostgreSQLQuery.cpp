#include "models/database/PostgreSQL/PostgreSQLQuery.h"

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
    if (parameter.empty()) this->queryParameters.append();
    else this->queryParameters.append(parameter);
}
