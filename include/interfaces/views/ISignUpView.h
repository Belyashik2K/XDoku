//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISIGNUPVIEW_H
#define ISIGNUPVIEW_H
#include "interfaces/IView.h"

class ISignUpView : public IView<class SignUpPresenter, ISignUpView>,
    std::enable_shared_from_this<ISignUpView>
{
public:
    void render() override = 0;
    // void init(std::unique_ptr<SignUpPresenter> &&presenter) override {
    //     this->setSelf(weak_from_this());
    //     std::unique_ptr<ISignUpPresenter> presenter = std::move(view);
    //     this->setPresenter();
    // }
    void init(std::unique_ptr<SignUpPresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //ISIGNUPVIEW_H
