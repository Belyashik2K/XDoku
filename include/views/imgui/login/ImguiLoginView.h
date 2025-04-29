//
// Created by belyashik2k on 4/27/25.
//

#ifndef IMGUILOGINVIEW_H
#define IMGUILOGINVIEW_H
#include "presenters/LoginPresenter.h"
#include "views/imgui/ImguiView.h"

class ImguiLoginView final : public IImguiView {
    LoginPresenter *presenter = nullptr;
public:
    void render() override;
    void setPresenter(LoginPresenter *p) { presenter = p; }
};

#endif //IMGUILOGINVIEW_H
