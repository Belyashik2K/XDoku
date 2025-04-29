//
// Created by belyashik2k on 4/24/25.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <cstdio>
#include <functional>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include "app_events/IEvent.h"

class EventBus {
    std::unordered_map<std::type_index, std::vector<std::function<void(const IEvent &)>>> handlers;

public:
    template<typename EventType>
    void subscribe(std::function<void(const EventType &)> handler) {
        auto wrapper = [handler](const IEvent &event) {
            handler(static_cast<const EventType &>(event));
        };
        handlers[typeid(EventType)].push_back(wrapper);
        // printf("[EventBus] Subscribed to event type: %s\n", typeid(EventType).name());
    }

    template<typename EventType>
    void publish(const EventType &event) {
        // printf("[EventBus] Publishing event of type: %s\n", typeid(EventType).name());

        if (const auto it = handlers.find(typeid(EventType)); it != handlers.end()) {
            for (const auto &handler: it->second) {
                handler(event);
            }
        } else {
            throw std::runtime_error("No handlers found for event type");
        }
    }
};

#endif //EVENTBUS_H
