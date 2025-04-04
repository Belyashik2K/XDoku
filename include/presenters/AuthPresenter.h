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
#include "views/auth/IAuthView.h"

class AuthPresenter : public IPresenter {
    std::shared_ptr<IUserRepository> userRepository;
    std::shared_ptr<IAuthView> view;
public:
    AuthPresenter(
        std::shared_ptr<IUserRepository> userRepository,
        std::shared_ptr<IAuthView> view
    ): userRepository(userRepository), view(std::move(view)) {}
    ~AuthPresenter() override = default;

    std::optional<User> authenticateUser() {
        view->showWelcomeMessage();

        std::ifstream file("/etc/machine-id");
        std::string hwid;
        if (file.is_open()) {
            std::getline(file, hwid);
            file.close();
        }

        if (hwid.empty()) {
            view->showAuthenticationResult(false);
            return std::nullopt;
        }

        const std::optional<std::string> savedUsername = userRepository->getUsernameBySessionId(hwid);
        if (savedUsername.has_value()) {
            User user = userRepository->get(savedUsername.value());
            view->showAuthenticationResult(true);
            return user;
        }

        auto [username, password] = view->getLoginCredentials();

        std::string hashedPassword = userRepository->getHashedPassword(username);
        const bool isPasswordValid = BCrypt::validatePassword(password, hashedPassword);
        if (!isPasswordValid) {
            view->showAuthenticationResult(false);
            return std::nullopt;
        }

        User authenticatedUser = userRepository->get(username);
        const bool result = userRepository->createSession(authenticatedUser.getId(), hwid);
        if (!result) {
            view->showAuthenticationResult(false);
            return std::nullopt;
        }

        view->showAuthenticationResult(true);
        return authenticatedUser;
    }
};

#endif //AUTHPRESENTER_H
