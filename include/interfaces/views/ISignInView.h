//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISIGNINVIEW_H
#define ISIGNINVIEW_H
#include "interfaces/IView.h"

class ISignInView : public IView<class SignInPresenter, ISignInView>,
                   public std::enable_shared_from_this<ISignInView> {
public:
    void render() override = 0;
    void init(std::unique_ptr<SignInPresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //ISIGNINVIEW_H
