//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef IHOWTOPLAYVIEW_H
#define IHOWTOPLAYVIEW_H
#include "interfaces/IView.h"

class IHowToPlayView : public IView<class HowToPlayPresenter, IHowToPlayView>,
                      public std::enable_shared_from_this<IHowToPlayView> {
public:
    void render() override = 0;
    void init(std::unique_ptr<HowToPlayPresenter> &&presenter) override {
        this->setSelf(weak_from_this());
        this->setPresenter(std::move(presenter));
    }
};

#endif //IHOWTOPLAYVIEW_H
