//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IMOVEREPOSITORY_H
#define IMOVEREPOSITORY_H
#include <any>

class IMoveRepository {
public:
    virtual ~IMoveRepository() = default;

    virtual std::any createMove(
        int gameId,
        int userId,
        std::any move
    ) = 0;
};

#endif //IMOVEREPOSITORY_H
