#ifndef IPRESENTER_H
#define IPRESENTER_H
#include "IView.h"

class IPresenter {
protected:
    IView *view = nullptr;
public:
    virtual ~IPresenter() = default;

    void render() const { if (view) view->render();}

    void setView(IView *v) { view = v; }
};

#endif
