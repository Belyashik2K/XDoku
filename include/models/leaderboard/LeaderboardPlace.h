//
// Created by belyashik2k on 4/8/25.
//

#ifndef LEADERBOARDPLACE_H
#define LEADERBOARDPLACE_H
#include <iostream>
#include <string>

class LeaderboardPlace {
    int place;
    std::string username;
    int rating;
public:
    LeaderboardPlace(const int place, std::string username, const int rating)
        : place(place), username(std::move(username)), rating(rating) {
    }
    void printInfo() const {
        const std::string infoString = std::format("{}. @{} - {} points", place, username, rating);
        std::cout << infoString << std::endl;
    }
};

#endif //LEADERBOARDPLACE_H
