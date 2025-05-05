//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISIGNINVIEW_H
#define ISIGNINVIEW_H
#include "core/IView.h"

class ISignInView : public IView<class SignInPresenter> {
public:
    void render() override = 0;
};

#endif //ISIGNINVIEW_H
