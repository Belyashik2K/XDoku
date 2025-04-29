//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IVIEW_H
#define IVIEW_H

class IPresenter;

class IView {
public:
    virtual ~IView() = default;

    virtual void render() = 0;
};

#endif //IVIEW_H
