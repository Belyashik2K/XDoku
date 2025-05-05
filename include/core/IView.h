//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IVIEW_H
#define IVIEW_H
#include <memory>

template<typename PresenterType>
class IView {
protected:
    std::weak_ptr<PresenterType> presenter;
public:
    virtual ~IView() = default;

    virtual void render() = 0;

    void setPresenter(const std::weak_ptr<PresenterType> &p) {
        presenter = p;
    }
};

#endif //IVIEW_H
