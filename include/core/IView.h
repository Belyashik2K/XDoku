//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IVIEW_H
#define IVIEW_H

class IView {
public:
    virtual void render() = 0;
    virtual ~IView() = default;
};

#endif //IVIEW_H
