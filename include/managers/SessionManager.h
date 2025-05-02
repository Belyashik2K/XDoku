//
// Created by belyashik2k on 5/2/25.
//

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include "core/EventBus.h"
#include "core/app_events/ApplicationEvents.h"
#include "core/app_events/UserEvents.h"
#include "core/database/repositories/ISessionRepository.h"
#include "models/custom_types/Timestamp.h"

class SessionManager {
    ISessionRepository *sessionRepository = nullptr;
    EventBus *eventBus = nullptr;

    void findActiveSession() const;
    void createSession(const OnUserLoggedIn &event) const;

    static bool isSessionExpired(const Timestamp &expiredAt);
    void onExpiredSessionFound(const std::string &sessionId) const;
    void onActiveSessionFound(int userId) const;
public:
    SessionManager(ISessionRepository *sessionRepository, EventBus *eventBus) :
        sessionRepository(sessionRepository), eventBus(eventBus) {}
    void subscribeToEvents() const;
};

#endif //SESSIONMANAGER_H
