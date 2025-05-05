//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IQUERY_H
#define IQUERY_H
#include <string>

template <typename ParamsType>
class IQuery {
protected:
    const std::string queryString;
    ParamsType queryParameters;
public:
    virtual ~IQuery() = default;

    virtual std::string getQueryString() const = 0;
    virtual ParamsType getQueryParameters() = 0;
    virtual void addParameter(const std::string &parameter) = 0;
};

#endif //IQUERY_H
