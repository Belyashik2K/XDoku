//
// Created by belyashik2k on 5/2/25.
//

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "domain/User.h"
#include "application/EventBus.h"
#include "application/app_events/UserEvents.h"
#include "interfaces/database/repositories/ISessionRepository.h"
#include "interfaces/database/repositories/IUserRepository.h"

class SessionManager {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<IUserRepository> userRepository;
    std::shared_ptr<ISessionRepository> sessionRepository;

    std::unique_ptr<User> currentUser = nullptr;

    static std::optional<std::string> getDeviceHWID();

    void findActiveSession();

    void createSession(const OnUserLoggedIn &event);

    static bool isSessionExpired(const Timestamp &expiredAt);

    void onExpiredSessionFound(const std::string &sessionId);

    void onActiveSessionFound(int userId);

    void subscribeToEvents();

    void logout();

    void updateCurrentUser(int userId);

    [[nodiscard]] std::unique_ptr<User> getUserById(int userId) const;

    void setCurrentUser(std::unique_ptr<User> user) {
        currentUser = std::move(user);
    }

    void clearCurrentUser() {
        currentUser.reset();
    }

public:
    SessionManager(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<ISessionRepository> &sessionRepository,
        const std::shared_ptr<IUserRepository> &userRepository
    ) : eventBus(eventBus), userRepository(userRepository), sessionRepository(sessionRepository) {
        subscribeToEvents();
    }

    User *getCurrentUser() {
        return currentUser.get();
    }

    [[nodiscard]] const User *getCurrentUser() const {
        return currentUser.get();
    }

    void addRating(int ratingChange) const;

    UserStats getUserStats() const;
};

#endif //SESSIONMANAGER_H
