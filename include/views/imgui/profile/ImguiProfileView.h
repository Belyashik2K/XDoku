//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUIPROFILEVIEW_H
#define IMGUIPROFILEVIEW_H
#include "presenters/ProfilePresenter.h"
#include "views/imgui/ImguiView.h"

class ImguiProfileView final : public IImguiView {
    ProfilePresenter *presenter = nullptr;
public:
    void render();
    void setPresenter(ProfilePresenter *p) { presenter = p; }
};

#endif //IMGUIPROFILEVIEW_H
