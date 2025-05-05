//
// Created by belyashik2k on 5/3/25.
//

#ifndef USERSTATS_H
#define USERSTATS_H
#include "User.h"

class UserStats {
    User *user;
    int gamesPlayed = 0;
    int gamesWon = 0;
    int gamesSurrendered = 0;
    int averageScore = 0;
    int averageTime = 0;
public:
    UserStats(
        User *user,
        const int gamesPlayed,
        const int gamesWon,
        const int gamesSurrendered,
        const int averageScore,
        const int averageTime
    ) : user(user), gamesPlayed(gamesPlayed), gamesWon(gamesWon),
        gamesSurrendered(gamesSurrendered), averageScore(averageScore),
        averageTime(averageTime) {}

    User *getUser() const { return user; }
    int getGamesPlayed() const { return gamesPlayed; }
    int getGamesWon() const { return gamesWon; }
    int getGamesSurrendered() const { return gamesSurrendered; }
    int getAverageScore() const { return averageScore; }
    int getAverageTime() const { return averageTime; }
};

#endif //USERSTATS_H
