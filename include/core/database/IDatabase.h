//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IDATABASE_H
#define IDATABASE_H

#include "iQuery.h"

template <typename T, typename U, typename V>
class IDatabase {
public:
    virtual ~IDatabase() = default;

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual V execute(IQuery<U> &query) = 0;
};

#endif //IDATABASE_H
