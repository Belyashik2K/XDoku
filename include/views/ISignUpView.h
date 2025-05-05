//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef ISIGNUPVIEW_H
#define ISIGNUPVIEW_H

#include "core/IView.h"

class ISignUpView : public IView<class SignUpPresenter> {
public:
    void render() override = 0;
};

#endif //ISIGNUPVIEW_H
