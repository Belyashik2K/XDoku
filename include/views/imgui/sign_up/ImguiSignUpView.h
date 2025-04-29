//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUISIGNUPVIEW_H
#define IMGUISIGNUPVIEW_H

#include "presenters/SignUpPresenter.h"
#include "views/imgui/ImguiView.h"

class ImguiSignUpView final : public IImguiView {
    SignUpPresenter *presenter = nullptr;
public:
    void render() override;
    void setPresenter(SignUpPresenter *p) { presenter = p; }
};

#endif //IMGUISIGNUPVIEW_H
