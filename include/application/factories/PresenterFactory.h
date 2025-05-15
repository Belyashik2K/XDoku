//
// Created by belyashik2k on 5/11/25.
//

#ifndef PRESENTERFACTORY_H
#define PRESENTERFACTORY_H
#include <memory>

class ViewFactory {
public:
    explicit ViewFactory() = default;

    template <typename ViewType, typename PresenterType, typename... Dependencies>
    std::shared_ptr<ViewType> create(Dependencies&&... deps) {
        auto view = std::make_shared<ViewType>();
        auto presenter = std::make_unique<PresenterType>(std::forward<Dependencies>(deps)...);
        view->init(std::move(presenter));
        return view;
    }
};

#endif //PRESENTERFACTORY_H
