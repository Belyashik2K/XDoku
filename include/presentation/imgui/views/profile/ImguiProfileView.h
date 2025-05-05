//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUIPROFILEVIEW_H
#define IMGUIPROFILEVIEW_H
#include "interfaces/views/IProfileView.h"

class ImguiProfileView final : public IProfileView {
public:
    void render() override;
};

#endif //IMGUIPROFILEVIEW_H
