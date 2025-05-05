//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef IPROFILEVIEW_H
#define IPROFILEVIEW_H
#include "core/IView.h"

class IProfileView : public IView<class ProfilePresenter> {
public:
    void render() override = 0;
};

#endif //IPROFILEVIEW_H
