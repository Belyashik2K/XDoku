//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef IVIEW_H
#define IVIEW_H
#include <memory>

class IBaseView {
public:
    virtual ~IBaseView() = default;
    virtual void render() = 0;
};

template<typename PresenterType, typename ViewType>
class IView : public IBaseView,
public std::enable_shared_from_this<ViewType>
{
protected:
    std::unique_ptr<PresenterType> presenter;
    std::weak_ptr<ViewType> self;
public:
    ~IView() override = default;

    void render() override = 0;

    void setPresenter(const std::weak_ptr<PresenterType> &p) {
        presenter = p;
    }

    void setSelf(const std::weak_ptr<ViewType> &ptr) {
        self = ptr;
    }

    void setPresenter(std::unique_ptr<PresenterType> &&p) {
        this->presenter = std::move(p);
        this->presenter->setView(self);
    }

    virtual void init(std::unique_ptr<PresenterType> &&presenter) {
        this->setSelf(this->weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //IVIEW_H
