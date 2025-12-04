//
// Created by belyashik2k on 5/2/25.
//

#include <fstream>
#include <memory>

#include "application/managers/SessionManager.h"
#include "application/app_events/ApplicationEvents.h"
#include "application/app_events/ButtonEvents.h"
#include "domain/UserStats.h"

static std::optional<std::string> cachedHWID = std::nullopt;

std::optional<std::string> SessionManager::getDeviceHWID() {
    // TODO: Implement a more secure way to get the HWID on different platforms

    if (cachedHWID.has_value()) {
        return cachedHWID;
    }

    std::ifstream file("/etc/machine-id");
    std::string hwid;
    if (file.is_open()) {
        std::getline(file, hwid);
        file.close();
    }

    if (hwid.empty()) {
        cachedHWID = std::nullopt;
    } else {
        cachedHWID = hwid;
    }

    return cachedHWID;
}

void SessionManager::findActiveSession() {
    const std::optional<std::string> HWID = getDeviceHWID();
    if (!HWID.has_value()) {
        printf("[SessionManager] HWID is not available, skipping session search...\n");
        return;
    }
    const std::optional<std::pair<int, Timestamp> > userIdAndExpiration = sessionRepository->
            getUserIdAndSessionExpiration(HWID.value());
    if (userIdAndExpiration.has_value()) {
        const int userId = userIdAndExpiration.value().first;
        const Timestamp expiration = userIdAndExpiration.value().second;
        printf(
            "[SessionManager] Found session for user ID: %d, expiration at: %s, validating...\n",
            userId,
            expiration.toString().c_str()
        );
        if (isSessionExpired(expiration)) {
            onExpiredSessionFound(HWID.value());
        } else {
            onActiveSessionFound(userIdAndExpiration.value().first);
        }
    } else {
        printf("[SessionManager] No active session found\n");
    }
}

void SessionManager::createSession(const OnUserLoggedIn &event) {
    const std::optional<std::string> HWID = getDeviceHWID();
    if (!HWID.has_value()) {
        printf("[SessionManager] HWID is not available, skipping session creation...\n");
        return;
    }

    if (sessionRepository->getUserIdBySessionId(HWID.value()).has_value()) {
        printf("[SessionManager] Session already exists for user ID: %d, skipping it...\n", event.userId);
        return;
    }

    if (sessionRepository->createSession(event.userId, HWID.value())) {
        printf("[SessionManager] Session created for user ID: %d\n", event.userId);
    } else {
        printf("[SessionManager] Failed to create session for user ID: %d\n", event.userId);
    }
    updateCurrentUser(event.userId);
}


void SessionManager::onActiveSessionFound(const int userId) {
    printf("[SessionManager] Session active, logging in user ID: %d\n", userId);
    updateCurrentUser(userId);
    eventBus->publish(OnUserLoggedIn(userId));
}

void SessionManager::onExpiredSessionFound(const std::string &sessionId) {
    printf("[SessionManager] Session expired, deleting...\n");
    logout();
}

bool SessionManager::isSessionExpired(const Timestamp &expiredAt) {
    return Timestamp::now() > expiredAt;
}

void SessionManager::logout() {
    printf("[SessionManager] Logging out...\n");
    const std::optional<std::string> HWID = getDeviceHWID();
    if (!HWID.has_value()) {
        printf("[SessionManager] HWID is not available, skipping logout...\n");
        return;
    }
    const bool result = sessionRepository->deleteSession(HWID.value());
    if (result) {
        printf("[SessionManager] Session deleted successfully\n");
    } else {
        printf("[SessionManager] Failed to delete session\n");
    }
    clearCurrentUser();
    eventBus->publish(OnUserLoggedOut());
}


void SessionManager::subscribeToEvents() {
    printf("[SessionManager] Subscribing to events...\n");
    eventBus->subscribe<OnApplicationStartup>([this](const OnApplicationStartup &) {
        findActiveSession();
    });
    eventBus->subscribe<OnUserLoggedIn>([this](const OnUserLoggedIn &event) {
        createSession(event);
    });
    eventBus->subscribe<OnLogoutButtonClicked>([this](const OnLogoutButtonClicked &) {
        logout();
    });
}

std::unique_ptr<User> SessionManager::getUserById(const int userId) const {
    std::optional<User> user = userRepository->get(userId);
    if (!user.has_value()) {
        return nullptr;
    }
    return std::make_unique<User>(user.value());
}


void SessionManager::updateCurrentUser(const int userId) {
    std::unique_ptr<User> user = getUserById(userId);
    if (!user) {
        printf("[SessionManager] User not found, logging out...\n");
        logout();
        return;
    }
    setCurrentUser(std::move(user));
}

void SessionManager::addRating(const int ratingChange) const {
    if (!currentUser) {
        printf("[SessionManager] No active user found, skipping rating update...\n");
        return;
    }
    const int current = currentUser->getRating();
    currentUser->setRating(std::max(0, current + ratingChange));
}

UserStats SessionManager::getUserStats() const {
    if (!currentUser) {
        printf("[SessionManager] No active user found, returning empty stats...\n");
        return UserStats();
    }
    return userRepository->getUserStats(currentUser->getId());
}
