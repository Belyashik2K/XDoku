//
// Created by belyashik2k on 5/3/25.
//

#ifndef IMGUIHOWTOPLAYVIEW_H
#define IMGUIHOWTOPLAYVIEW_H
#include <string>

#include "interfaces/views/IHowToPlayView.h"

class ImguiHowToPlayView final : public IHowToPlayView {
public:
    void render() override;

    void renderCurrentBackground() const;

    void renderCurrentFAQ() const;

    static void renderFAQ(const std::string &header, const std::string &description);

    static void renderOverviewFAQ();

    static void renderNumberPlacementFAQ();

    static void renderCellSelectionFAQ();

    static void renderDifficultyFAQ();

    void renderButtons() const;
};

#endif //IMGUIHOWTOPLAYVIEW_H
