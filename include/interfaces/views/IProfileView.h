//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef IPROFILEVIEW_H
#define IPROFILEVIEW_H
#include "interfaces/IView.h"

class IProfileView : public IView<class ProfilePresenter, IProfileView>,
                    public std::enable_shared_from_this<IProfileView> {
public:
    void render() override = 0;
    void init(std::unique_ptr<ProfilePresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //IPROFILEVIEW_H
