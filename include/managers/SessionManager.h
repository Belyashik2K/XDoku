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

    void findActiveSession();
    void createSession(const OnUserLoggedIn &event) const;

    bool isSessionExpired(Timestamp expiredAt) const;
    void onExpiredSessionFound();
    void onActiveSessionFound() const;
public:
    SessionManager(ISessionRepository *sessionRepository, EventBus *eventBus) :
        sessionRepository(sessionRepository), eventBus(eventBus) {}
    void subscribeToEvents();
};

#endif //SESSIONMANAGER_H
