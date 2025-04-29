//
// Created by belyashik2k on 4/27/25.
//

#ifndef IMGUILOGINVIEW_H
#define IMGUILOGINVIEW_H
#include "presenters/LoginPresenter.h"
#include "views/imgui/ImguiView.h"

class ImguiSignInView final : public IImguiView {
    SignInPresenter *presenter = nullptr;
public:
    void render() override;
    void setPresenter(SignInPresenter *p) { presenter = p; }
};

#endif //IMGUILOGINVIEW_H
