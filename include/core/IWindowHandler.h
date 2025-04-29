//
// Created by belyashik2k on 4/29/25.
//

#ifndef IWINDOWHANDLER_H
#define IWINDOWHANDLER_H
#include <functional>

class IWindowHandler {
public:
    virtual void run(std::function<void()> renderCallback) = 0;
    virtual void shutdown() = 0;
    virtual ~IWindowHandler() = default;
};

#endif //IWINDOWHANDLER_H
