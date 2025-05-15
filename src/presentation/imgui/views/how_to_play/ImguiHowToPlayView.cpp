//
// Created by belyashik2k on 5/3/25.
//

#include "presentation/imgui/views/how_to_play/ImguiHowToPlayView.h"

#include "application/presenters/HowToPlayPresenter.h"
#include "domain/sudoku/enums/SudokuDifficulty.h"
#include "presentation/imgui/ImguiColors.h"
#include "presentation/imgui/ImguiUtils.h"
#include "presentation/imgui/guards/ImguiChildWindowGuard.h"
#include "presentation/imgui/guards/ImguiWindowGuard.h"

void ImguiHowToPlayView::render() {
    ImguiWindowGuard window("How to play",
                            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);

    {
        renderCurrentBackground();

        const ImVec2 windowSize = ImGui::GetWindowSize();
        ImGui::SetCursorPosX(windowSize.x * 0.6f);
        ImguiChildWindowGuard childWindow(
        "InfoArea",
        ImVec2(windowSize.x * 0.40f, windowSize.y),
        ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize,
        false
    );
        const ImVec2 childWindowSize = ImGui::GetWindowSize();
        ImGui::SetCursorPosY(childWindowSize.y * 0.22f);

        renderCurrentFAQ();
        renderButtons();
    }

}

void ImguiHowToPlayView::renderCurrentBackground() const {
    const std::string basePath = "../assets/textures/how_to_play/";
    switch (presenter->getCurrentFAQType()) {
        case FAQType::DIFFICULTY:
            ImguiUtils::updateBackground(basePath + "ds_background.jpg");
            break;
        case FAQType::CELL_SELECTION:
            ImguiUtils::updateBackground(basePath + "cs_background.jpg");
            break;
        case FAQType::NUMBER_PLACEMENT:
            ImguiUtils::updateBackground(basePath + "np_background.jpg");
            break;
        case FAQType::OVERVIEW:
            ImguiUtils::updateBackground(basePath + "o_background.jpg");
            break;
        default:
            throw std::runtime_error("Unrecognized FAQ type");
    }
}

void ImguiHowToPlayView::renderCurrentFAQ() const {
    switch (presenter->getCurrentFAQType()) {
        case FAQType::DIFFICULTY:
            renderDifficultyFAQ();
            break;
        case FAQType::CELL_SELECTION:
            renderCellSelectionFAQ();
            break;
        case FAQType::NUMBER_PLACEMENT:
            renderNumberPlacementFAQ();
            break;
        case FAQType::OVERVIEW:
            renderOverviewFAQ();
            break;
        default:
            throw std::runtime_error("Unrecognized FAQ type");
    }
}

void ImguiHowToPlayView::renderOverviewFAQ() {
    const std::string header = "Overview";
    const std::string description = R"(
At the end of the game, you will see game summary.

For example, you can see:
- Difficulty level of played game
- Mistakes count, if any
- Elapsed time for solving the board
- Rating, which you gained for solving the board

After finishing the game, you can see your new rating
in profile and also in leaderboard.

Have fun with XDoku!
)";
    renderFAQ(header, description);
}

void ImguiHowToPlayView::renderNumberPlacementFAQ() {
    const std::string header = "Place number";
    const std::string description = R"(
Next, you need to place a number in the selected cell.

To do this, you need to select the number on your keyboard

If your placed number is correct, the cell will be deactivated.
If the number is incorrect, the cell will be highlighted
with red color.

All mistakes and elapsed time will influence on your rating
at the end of the game.

All progress will be saved automatically.
)";
    renderFAQ(header, description);
}

void ImguiHowToPlayView::renderCellSelectionFAQ() {
    const std::string header = "Select cell";
    const std::string description = R"(
After you select the difficulty level, you will see a sudoku grid.

Let's say about some rules of the game:
- Your goal is to fill the empty cells with numbers from 1 to 9.
- Your placed numbers must not repeat in the same row,
column or 3x3 square.
- In result, you should get a completed sudoku field.

For example, I clicked on the cell in the sixth row
and the sixth column.

)";
    renderFAQ(header, description);
}

void ImguiHowToPlayView::renderDifficultyFAQ() {
    const std::string header = "Select difficulty";
    const std::string description = std::format(R"(
Firstly, you need to click "Play" button in the main menu.
Then, you must select the difficulty level of the game.

The higher the level, the more difficult the game will be.

For example:
- Easy: {} cells are open
- Medium: {} cells are open
- Hard: {} cells are open
- Expert: {} cells are open

)",
        SudokuDifficulty::getSettings(SudokuDifficultyEnum::EASY).openCellsCount,
        SudokuDifficulty::getSettings(SudokuDifficultyEnum::MEDIUM).openCellsCount,
        SudokuDifficulty::getSettings(SudokuDifficultyEnum::HARD).openCellsCount,
        SudokuDifficulty::getSettings(SudokuDifficultyEnum::EXPERT).openCellsCount
    );

    renderFAQ(header, description);
}

void ImguiHowToPlayView::renderButtons() const {
    const ImVec2 windowSize = ImGui::GetWindowSize();

    ImguiUtils::createButton(
         "next_faq_button",
         "Next",
         ImVec2(windowSize.x * 0.6f, 60),
         [this] {
             presenter->onNextButtonClicked();
         },
         nullptr,
         true
     );

    ImguiUtils::addVerticalSpacing(2);

    ImguiUtils::createButton(
        "back_button",
        "Back to menu",
        ImVec2(windowSize.x * 0.6f, 60),
        [this] {
            presenter->onBackButtonClicked();
        },
        nullptr,
        true
    );
}

void ImguiHowToPlayView::renderFAQ(const std::string &header, const std::string &description) {
    ImguiUtils::printText(
        header.c_str(),
        BLACK,
        36,
        true
    );
    ImguiUtils::addVerticalSpacing(4);
    ImguiUtils::printText(
        description.c_str(),
        BLACK,
        32,
        false
    );
    ImguiUtils::addVerticalSpacing(4);
}
