//
// Created by belyashik2k on 4/25/25.
//

#include <stdexcept>
#include <core/EventBus.h>

void EventBus::publish(const IEvent &event) {
    if (const auto it = handlers.find(typeid(event)); it != handlers.end()) {
        for (const auto &handler : it->second) {
            handler(event);
        }
    } else {
        throw std::runtime_error("No handlers found for event type");
    }
}

template<typename EventType>
void EventBus::subscribe(std::function<void(const EventType &)> handler) {
    auto wrapper = [handler](const IEvent &event) {
        handler(static_cast<const EventType &>(event));
    };
    handlers[typeid(EventType)].push_back(wrapper);
}
