//
// Created by Belyashik2K on 31.03.2025.
//

#ifndef AUTHPRESENTER_H
#define AUTHPRESENTER_H
#include <iostream>
#include <memory>
#include <utility>

#include "core/database/repositories/IUserRepository.h"
#include "views/auth/IAuthView.h"

template <typename Connection, typename Params, typename Result>
class AuthPresenter {
    std::shared_ptr<IUserRepository<Connection, Params, Result>> userRepository;
    std::shared_ptr<IAuthView> view;
public:
    AuthPresenter(
        std::shared_ptr<IUserRepository<Connection, Params, Result>> userRepository,
        std::shared_ptr<IAuthView> view
    ): userRepository(userRepository), view(std::move(view)) {}

    std::optional<User> authenticateUser() {
        view->showWelcomeMessage();

        auto [username, password] = view->getLoginCredentials();

        std::string hashedPassword = userRepository->getHashedPassword(username);
        const bool isPasswordValid = BCrypt::validatePassword(password, hashedPassword);
        if (!isPasswordValid) {
            view->showAuthenticationResult(false);
            return std::nullopt;
        }


        view->showAuthenticationResult(true);
        return userRepository->get(username);
    }
};

#endif //AUTHPRESENTER_H
