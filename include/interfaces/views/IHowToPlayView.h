//
// Created by Belyashik2K on 05.05.2025.
//

#ifndef IHOWTOPLAYVIEW_H
#define IHOWTOPLAYVIEW_H
#include "interfaces/IView.h"

class IHowToPlayView : public IView<class HowToPlayPresenter, IHowToPlayView>{
public:
    void render() override = 0;
};

#endif //IHOWTOPLAYVIEW_H
