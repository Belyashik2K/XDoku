//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef AUTHPRESENTER_H
#define AUTHPRESENTER_H
#include <fstream>
#include <memory>
#include <utility>

#include "core/IPresenter.h"
#include "core/database/repositories/IUserRepository.h"
#include "core/database/repositories/ISessionRepository.h"
#include "views/auth/IAuthView.h"

class AuthPresenter : public IPresenter {
    std::shared_ptr<IUserRepository> userRepository;
    std::shared_ptr<ISessionRepository> sessionRepository;
    std::shared_ptr<IAuthView> view;
public:
    AuthPresenter(
        std::shared_ptr<IUserRepository> userRepository,
        std::shared_ptr<ISessionRepository> sessionRepository,
        std::shared_ptr<IAuthView> view
    ): userRepository(std::move(userRepository)), sessionRepository(std::move(sessionRepository)), view(std::move(view)) {}
    ~AuthPresenter() override = default;

    void run() const;
    std::optional<User> authenticateUser() const;
    std::optional<User> registerUser() const;
};

#endif //AUTHPRESENTER_H
