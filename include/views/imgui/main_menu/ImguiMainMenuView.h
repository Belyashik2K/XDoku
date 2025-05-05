//
// Created by belyashik2k on 5/2/25.
//

#ifndef IMGUIMAINMENUVIEW_H
#define IMGUIMAINMENUVIEW_H
#include "views/IMainMenuView.h"

class ImguiMainMenuView final : public IMainMenuView {
public:
    void render() override;

    void renderMainMenu() const;

    void renderFormButtons() const;
};

#endif //IMGUIMAINMENUVIEW_H
