//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef IMAINMENUVIEW_H
#define IMAINMENUVIEW_H

#include "core/IView.h"

class IMainMenuView : public IView<class MainMenuPresenter> {
public:
    void render() override = 0;
};

#endif //IMAINMENUVIEW_H
