//
// Created by belyashik2k on 5/2/25.
//

#ifndef IMGUIMAINMENUVIEW_H
#define IMGUIMAINMENUVIEW_H
#include "presenters/MainMenuPresenter.h"
#include "views/IMainMenuView.h"
#include "views/imgui/ImguiView.h"

class ImguiMainMenuView final : public IMainMenuView {
    MainMenuPresenter *presenter = nullptr;
public:
    void render() override;

    void renderMainMenu() const;

    void renderFormButtons() const;

    void setPresenter(MainMenuPresenter *p) { presenter = p; }
};

#endif //IMGUIMAINMENUVIEW_H
