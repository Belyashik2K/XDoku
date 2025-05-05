//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUIHOWTOPLAYVIEW_H
#define IMGUIHOWTOPLAYVIEW_H
#include "presenters/HowToPlayPresenter.h"
#include "views/imgui/ImguiView.h"

class ImguiHowToPlayView final : public IImguiView {
    HowToPlayPresenter *presenter = nullptr;
public:
    void render();
    void setPresenter(HowToPlayPresenter *p) { presenter = p; }
};

#endif //IMGUIHOWTOPLAYVIEW_H
