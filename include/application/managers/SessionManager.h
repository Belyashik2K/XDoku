//
// Created by belyashik2k on 5/2/25.
//

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "application/EventBus.h"
#include "application/app_events/UserEvents.h"
#include "interfaces/database/repositories/ISessionRepository.h"

class SessionManager {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<ISessionRepository> sessionRepository;

    static std::optional<std::string> getDeviceHWID() ;

    void findActiveSession() const;

    void createSession(const OnUserLoggedIn &event) const;

    static bool isSessionExpired(const Timestamp &expiredAt);

    void onExpiredSessionFound(const std::string &sessionId) const;

    void onActiveSessionFound(int userId) const;

    void subscribeToEvents() const;

public:
    SessionManager(
        const std::shared_ptr<EventBus> &eventBus,
        const std::shared_ptr<ISessionRepository> &sessionRepository
    ) : eventBus(eventBus), sessionRepository(sessionRepository) {
        subscribeToEvents();
    }
};

#endif //SESSIONMANAGER_H
