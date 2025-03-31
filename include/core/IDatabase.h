//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IDATABASE_H
#define IDATABASE_H
#include <string>

template <typename T>
class IDatabase {
public:
    IDatabase() = default;
    virtual ~IDatabase() = default;

    virtual T connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool isConnected(const T &connection) = 0;

    virtual bool createUser(const std::string& username, const std::string& password) = 0;
    virtual bool authenticateUser(const std::string& username, const std::string& password) = 0;
};

#endif //IDATABASE_H
