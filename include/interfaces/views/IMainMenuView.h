//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef IMAINMENUVIEW_H
#define IMAINMENUVIEW_H
#include "interfaces/IView.h"

class IMainMenuView : public IView<class MainMenuPresenter , IMainMenuView>,
                     public std::enable_shared_from_this<IMainMenuView> {
public:
    void render() override = 0;
    void init(std::unique_ptr<MainMenuPresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //IMAINMENUVIEW_H
