//
// Created by belyashik2k on 4/25/25.
//

#include <stdexcept>
#include <core/EventBus.h>

void EventBus::publish(const IEvent &event) {
    if (const auto it = handlers.find(typeid(event)); it != handlers.end()) {
        it->second(event);
    } else {
        throw std::runtime_error("No handler found for event type");
    }
}

template<typename EventType>
void EventBus::subscribe(std::function<void(const EventType &)> handler) {
    handlers[typeid(EventType)] = [handler](const IEvent &event) {
        handler(static_cast<const EventType &>(event));
    };
}
