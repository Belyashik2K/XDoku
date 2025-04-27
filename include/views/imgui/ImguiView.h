//
// Created by belyashik2k on 4/27/25.
//

#ifndef IMGUIVIEW_H
#define IMGUIVIEW_H
#include "core/IView.h"

class IImguiView : public IView {
public:
    void render() override = 0;
};

#endif //IMGUIVIEW_H
