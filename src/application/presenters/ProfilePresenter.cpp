//
// Created by belyashik2k on 5/5/25.
//

#include "application/presenters/ProfilePresenter.h"

#include "application/app_events/ButtonEvents.h"

void ProfilePresenter::onBackButtonClicked() const{
    eventBus->publish(OnBackButtonClicked());
}

void ProfilePresenter::onLogoutButtonClicked() const{
    eventBus->publish(OnLogoutButtonClicked());
}

int ProfilePresenter::getGamesCount() const{
    return userStats->getTotalGames();
}

int ProfilePresenter::getFinishedGamesCount() const{
    return userStats->getFinishedGames();
}

int ProfilePresenter::getCompletionRate() const{
    return userStats->getCompletionRate();
}

std::string ProfilePresenter::getMostCommonDifficulty() const{
    if (userStats->getMostCommonDifficulty() == SudokuDifficultyEnum::UNKNOWN) {
        return "Unknown";
    }
    return SudokuDifficulty::getDifficultyName(userStats->getMostCommonDifficulty());
}

std::string ProfilePresenter::getAverageSolutionTime() const {
    const int averageTimeSeconds = userStats->getAverageSolutionTimeSeconds();
    const int hours = averageTimeSeconds / 3600;
    const int minutes = averageTimeSeconds % 3600 / 60;
    const int seconds = averageTimeSeconds % 60;
    std::string averageTime;
    if (hours) averageTime += std::format("{:02d}:", hours);
    averageTime += std::format("{:02d}:", minutes);
    averageTime += std::format("{:02d}", seconds);
    if (averageTime.empty()) averageTime = "00:00";
    return averageTime;
}