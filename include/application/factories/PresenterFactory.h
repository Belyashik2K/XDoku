//
// Created by belyashik2k on 5/11/25.
//

#ifndef PRESENTERFACTORY_H
#define PRESENTERFACTORY_H
#include <memory>

class PresenterFactory {
public:
    explicit PresenterFactory() = default;

    template <typename ViewType, typename PresenterType, typename... Dependencies>
    std::shared_ptr<PresenterType> create(Dependencies&&... deps) {
        auto view = std::make_unique<ViewType>();
        auto presenter = std::make_shared<PresenterType>(std::forward<Dependencies>(deps)...);
        presenter->init(std::move(view));
        return presenter;
    }
};

#endif //PRESENTERFACTORY_H
