#ifndef IPRESENTER_H
#define IPRESENTER_H
#include "IView.h"

class IBasePresenter {
public:
    virtual void render() const = 0;
    virtual ~IBasePresenter() = default;
};

template <typename ViewType, typename PresenterType>
class IPresenter : public IBasePresenter {
protected:
    std::unique_ptr<ViewType> view;
    std::weak_ptr<PresenterType> self;
public:
    ~IPresenter() override = default;

    void render() const override {
        if (view) {
            view->render();
        }
    }

    void setSelf(const std::weak_ptr<PresenterType>& ptr) {
        self = ptr;
    }

    void setView(std::unique_ptr<ViewType>&& view) {
        this->view = std::move(view);
        this->view->setPresenter(self);
    }

    virtual void init(std::unique_ptr<ViewType> &&view) = 0;
};

#endif
