//
// Created by belyashik2k on 5/2/25.
//

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include "core/EventBus.h"
#include "core/app_events/UserEvents.h"
#include "core/database/repositories/ISessionRepository.h"
#include "models/custom_types/Timestamp.h"

class SessionManager {
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<ISessionRepository> sessionRepository;

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
