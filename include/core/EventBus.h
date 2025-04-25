//
// Created by belyashik2k on 4/24/25.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <functional>
#include <typeindex>
#include <unordered_map>
#include "app_events/IEvent.h"

class EventBus {
    std::pmr::unordered_map<std::type_index, std::function<void(const IEvent&)>> handlers;
public:
    template<typename EventType>
    void subscribe(std::function<void(const EventType&)> handler);

    void publish(const IEvent& event);
};

#endif //EVENTBUS_H
