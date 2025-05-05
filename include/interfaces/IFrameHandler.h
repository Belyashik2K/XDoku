//
// Created by belyashik2k on 4/29/25.
//

#ifndef IFRAMEHANDLER_H
#define IFRAMEHANDLER_H
#include <functional>

class IFrameHandler {
public:
    virtual void run(std::function<void()> renderCallback) = 0;
    virtual void shutdown() = 0;
    virtual ~IFrameHandler() = default;
};

#endif //IFRAMEHANDLER_H
