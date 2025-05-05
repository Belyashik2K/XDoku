//
// Created by belyashik2k on 4/27/25.
//

#ifndef IMGUILOGINVIEW_H
#define IMGUILOGINVIEW_H
#include "interfaces/views/ISignInView.h"

class ImguiSignInView final : public ISignInView {
public:
    void render() override;

    void renderLoginForm() const;

    void renderLoginError() const;

    static void renderFormHeader();

    void renderFormInputs() const;

    void renderFormButtons() const;
};

#endif //IMGUILOGINVIEW_H
