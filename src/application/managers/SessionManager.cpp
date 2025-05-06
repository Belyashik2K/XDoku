//
// Created by belyashik2k on 5/2/25.
//

#include <fstream>


#include "application/managers/SessionManager.h"
#include "application/app_events/ApplicationEvents.h"
#include "application/app_events/ButtonEvents.h"

std::optional<std::string> SessionManager::getDeviceHWID() {
    // TODO: Implement a more secure way to get the HWID on different platforms
    std::ifstream file("/etc/machine-id");
    std::string hwid;
    if (file.is_open()) {
        std::getline(file, hwid);
        file.close();
    }

    if (hwid.empty()) {
        return std::nullopt;
    }
    return hwid;
}

void SessionManager::findActiveSession() const {
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

void SessionManager::createSession(const OnUserLoggedIn &event) const {
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
}


void SessionManager::onActiveSessionFound(const int userId) const {
    printf("[SessionManager] Session active, logging in user ID: %d\n", userId);
    eventBus->publish(OnUserLoggedIn(userId));
}

void SessionManager::onExpiredSessionFound(const std::string &sessionId) const {
    printf("[SessionManager] Session expired, deleting...\n");
    logout();
}

bool SessionManager::isSessionExpired(const Timestamp &expiredAt) {
    return Timestamp::now() > expiredAt;
}

void SessionManager::logout() const {
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
    eventBus->publish(OnUserLoggedOut());
}


void SessionManager::subscribeToEvents() const {
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
