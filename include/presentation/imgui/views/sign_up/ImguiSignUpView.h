//
// Created by belyashik2k on 4/29/25.
//

#ifndef IMGUISIGNUPVIEW_H
#define IMGUISIGNUPVIEW_H
#include "interfaces/views/ISignUpView.h"

class ImguiSignUpView final : public ISignUpView {
public:
    void render() override;

    void renderSignUpError() const;

    void renderSignUpForm() const;

    static void renderFormHeader();

    void renderFormInputs() const;

    void renderFormButtons() const;
};

#endif //IMGUISIGNUPVIEW_H
