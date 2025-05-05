//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUIHOWTOPLAYVIEW_H
#define IMGUIHOWTOPLAYVIEW_H
#include "interfaces/views/IHowToPlayView.h"

class ImguiHowToPlayView final : public IHowToPlayView {
public:
    void render() override;
};

#endif //IMGUIHOWTOPLAYVIEW_H
