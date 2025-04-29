//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUISIGNUPVIEW_H
#define IMGUISIGNUPVIEW_H

#include "presenters/RegisterPresenter.h"
#include "views/imgui/ImguiView.h"

class ImguiSignUpView final : public IImguiView {
    RegisterPresenter *presenter = nullptr;
public:
    void render() override;
    void setPresenter(RegisterPresenter *p) { presenter = p; }
};

#endif //IMGUISIGNUPVIEW_H
