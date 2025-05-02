//
// Created by belyashik2k on 5/2/25.
//

#include "managers/SessionManager.h"

#include "utils.h"
#include "core/app_events/ApplicationEvents.h"
#include "core/app_events/UserEvents.h"

void SessionManager::findActiveSession() {
    const std::optional<std::string> HWID = getDeviceHWID();
    if (!HWID.has_value()) {
        printf("HWID is not available\n");
        return;
    }
    const std::optional<std::string> session = sessionRepository->getUsernameBySessionId(*HWID);
    if (session.has_value()) {
        printf("Active session found for user: %s\n", session->c_str());
        if (isSessionExpired(Timestamp("2025-04-07 20:51:31.675962"))) {
            onExpiredSessionFound();
        }
        onActiveSessionFound();
    } else {
        printf("No active session found\n");
    }
}

void SessionManager::createSession(const OnUserLoggedIn &event) const {
    const std::optional<std::string> HWID = getDeviceHWID();
    if (!HWID.has_value()) {
        printf("HWID is not available\n");
        return;
    }
    try {
        const bool sessionCreationStatus = sessionRepository->createSession(event.userId, *HWID);
        printf("Session creation status: %s\n", sessionCreationStatus ? "Success" : "Failed");
    } catch (const std::exception &e) {
        printf("Error creating session: %s\n", e.what());
    }
}


void SessionManager::onActiveSessionFound() const {
    eventBus->publish(OnUserLoggedIn(69));
}

void SessionManager::onExpiredSessionFound() {
}

bool SessionManager::isSessionExpired(Timestamp expiredAt) const {
    return 0;
}

void SessionManager::subscribeToEvents() {
    eventBus->subscribe<OnApplicationStartup>([this](const OnApplicationStartup &) {
        findActiveSession();
    });
    eventBus->subscribe<OnUserLoggedIn>([this](const OnUserLoggedIn &event) {
        createSession(event);
    });
}
