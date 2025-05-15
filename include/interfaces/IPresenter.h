#ifndef IPRESENTER_H
#define IPRESENTER_H
#include "IView.h"

class IBasePresenter {
public:
    virtual ~IBasePresenter() = default;
};

template <typename ViewType>
class IPresenter : public IBasePresenter {
protected:
    std::weak_ptr<ViewType> view;
public:
    ~IPresenter() override = default;

    void setView(const std::weak_ptr<ViewType> &view) {
        this->view = view;
    }

    std::shared_ptr<ViewType> getView() const {
        return view.lock();
    }
};

#endif
