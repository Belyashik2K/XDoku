cmake_minimum_required(VERSION 3.30)
project(XDoku)

set(CMAKE_CXX_STANDARD 20)

find_package(PostgreSQL REQUIRED)
# Not REQUIRED: some distro packages (e.g. Debian/Ubuntu's libpqxx-dev) don't ship a CMake
# config file at all, only a plain library + headers on the default system paths. REQUIRED
# here would hard-fail configuration on those before ever reaching the libpqxx::pqxx-vs-plain
# "pqxx" fallback below, which exists specifically to handle that case.
find_package(libpqxx CONFIG QUIET)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

if (NOT WIN32)
    enable_language(ASM)
else ()
    # Windows.h pulls in a huge surface area by default (winsock, GDI, crypto, COM...)
    # which conflicts with vendored deps (bcrypt) and can clash with modern Windows
    # SDK headers (ncrypt.h) when compiled without these trimmed down. NOMINMAX avoids
    # windows.h's min/max macros shadowing std::min/std::max used throughout the code.
    add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)
endif ()

add_executable(XDoku
        src/run.cpp
        deps/glad/glad-4-3/src/glad.c
        deps/imgui/imgui.cpp
        deps/imgui/imgui_draw.cpp
        deps/imgui/imgui_widgets.cpp
        deps/imgui/imgui_tables.cpp
        deps/imgui/imgui_demo.cpp
        deps/imgui/backends/imgui_impl_glfw.cpp
        deps/imgui/backends/imgui_impl_opengl3.cpp
        deps/bcrypt/src/bcrypt.c
        deps/bcrypt/src/crypt_blowfish.c
        deps/bcrypt/src/crypt_gensalt.c
        deps/bcrypt/src/wrapper.c
        include/infrastructure/config/EnvConfig.h
        src/infrastructure/config/EnvConfig.cpp
        include/infrastructure/platform/HardwareId.h
        src/infrastructure/platform/HardwareId.cpp
        include/interfaces/IView.h
        include/interfaces/IPresenter.h
        include/domain/User.h
        include/interfaces/database/IDatabase.h
        include/infrastructure/database/PostgreSQL/PostgreSQLDatabase.h
        src/infrastructure/database/PostgreSQL/PostgreSQLDatabase.cpp
        include/infrastructure/database/PostgreSQL/PostgreSQLDatabase.h
        include/infrastructure/database/PostgreSQL/repositories/PostgreSQLUserRepository.h
        include/interfaces/database/repositories/IUserRepository.h
        src/infrastructure/database/PostgreSQL/repositories/PostgreSQLUserRepository.cpp
        include/interfaces/database/iQuery.h
        include/interfaces/database/iQuery.h
        src/infrastructure/database/PostgreSQL/PostgreSQLQuery.cpp
        include/infrastructure/database/PostgreSQL/PostgreSQLQuery.h
        include/domain/custom_types/Timestamp.h
        src/domain/custom_types/Timestamp.cpp
        src/domain/User.cpp
        include/interfaces/database/repositories/IGameRepository.h
        include/interfaces/database/repositories/IMoveRepository.h
        include/interfaces/database/repositories/ISessionRepository.h
        include/interfaces/database/repositories/IRatingRepository.h
        include/domain/sudoku/SudokuGame.h
        include/domain/sudoku/SudokuGrid.h
        include/domain/sudoku/SudokuCell.h
        include/domain/sudoku/enums/SudokuDifficulty.h
        include/domain/sudoku/utils/SudokuGenerator.h
        include/domain/sudoku/enums/SudokuGameStatus.h
        src/domain/sudoku/enums/SudokuDifficulty.cpp
        src/domain/sudoku/enums/SudokuGameStatus.cpp
        src/domain/sudoku/utils/SudokuGenerator.cpp
        src/domain/sudoku/SudokuCell.cpp
        src/domain/sudoku/SudokuGrid.cpp
        src/infrastructure/database/PostgreSQL/repositories/PostgreSQLSessionRepository.cpp
        include/infrastructure/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h
        src/domain/sudoku/SudokuGame.cpp
        include/infrastructure/database/PostgreSQL/repositories/PostgreSQLGameRepository.h
        src/infrastructure/database/PostgreSQL/repositories/PostgreSQLGameRepository.cpp
        include/infrastructure/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h
        src/infrastructure/database/PostgreSQL/repositories/PostgreSQLRatingRepository.cpp
        include/infrastructure/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h
        src/infrastructure/database/PostgreSQL/repositories/PostgreSQLMoveRepository.cpp
        include/domain/leaderboard/LeaderboardPlace.h
        include/domain/sudoku/SudokuMove.h
        src/domain/sudoku/SudokuMove.cpp
        include/interfaces/IEvent.h
        include/application/EventBus.h
        include/application/AppMediator.h
        include/Application.h
        src/application/EventBus.cpp
        src/application/AppMediator.cpp
        include/application/presenters/SignInPresenter.h
        include/presentation/imgui/views/sign_in/ImguiSignInView.h
        include/presentation/imgui/ImguiUtils.h
        src/presentation/imgui/views/sign_in/ImguiSignInView.cpp
        src/application/presenters/SignInPresenter.cpp
        include/interfaces/IFrameHandler.h
        include/presentation/imgui/ImguiFrameHandler.h
        src/presentation/imgui/ImguiFrameHandler.cpp
        src/Application.cpp
        include/presentation/imgui/managers/ImguiTextureManager.h
        src/presentation/imgui/managers/ImguiTextureManager.cpp
        include/presentation/imgui/guards/ImguiWindowGuard.h
        include/presentation/imgui/guards/ImguiChildWindowGuard.h
        src/presentation/imgui/guards/ImguiWindowGuard.cpp
        src/presentation/imgui/guards/ImguiChildWindowGuard.cpp
        src/presentation/imgui/ImguiUtils.cpp
        src/presentation/imgui/views/sign_up/ImguiSignUpView.cpp
        include/presentation/imgui/views/sign_up/ImguiSignUpView.h
        include/application/presenters/SignUpPresenter.h
        include/application/app_events/ButtonEvents.h
        src/application/presenters/SignUpPresenter.cpp
        src/presentation/imgui/guards/ImguiStyleVarGuard.cpp
        src/presentation/imgui/guards/ImguiStyleColorGuard.cpp
        include/presentation/imgui/guards/ImguiStyleVarGuard.h
        include/application/app_events/UserEvents.h
        include/presentation/imgui/guards/ImguiStyleColorGuard.h
        include/presentation/imgui/managers/ImguiFontManager.h
        src/presentation/imgui/managers/ImguiFontManager.cpp
        include/application/app_events/ApplicationEvents.h
        src/application/presenters/MainMenuPresenter.cpp
        include/application/presenters/MainMenuPresenter.h
        src/presentation/imgui/views/main_menu/ImguiMainMenuView.cpp
        include/presentation/imgui/views/main_menu/ImguiMainMenuView.h
        include/application/managers/SessionManager.h
        src/application/managers/SessionManager.cpp
        include/presentation/imgui/ImguiColors.h
        src/presentation/imgui/views/leaderboard/ImguiLeaderboardView.cpp
        include/presentation/imgui/views/leaderboard/ImguiLeaderboardView.h
        include/application/presenters/LeaderboardPresenter.h
        src/application/presenters/LeaderboardPresenter.cpp
        src/application/managers/SudokuGameManager.cpp
        include/application/managers/SudokuGameManager.h
        src/presentation/imgui/views/game/ImguiSudokuGameView.cpp
        src/presentation/imgui/views/game/ImguiSudokuGameDifficultySelectorView.cpp
        src/application/presenters/game/SudokuGamePresenter.cpp
        src/application/presenters/game/SudokuGameDifficultySelectorPresenter.cpp
        include/application/presenters/game/SudokuGameDifficultySelectorPresenter.h
        include/application/presenters/game/SudokuGamePresenter.h
        include/presentation/imgui/views/game/ImguiSudokuGameDifficultySelectorView.h
        include/presentation/imgui/views/game/ImguiSudokuGameView.h
        include/presentation/imgui/views/profile/ImguiProfileView.h
        include/application/presenters/ProfilePresenter.h
        src/presentation/imgui/views/profile/ImguiProfileView.cpp
        src/presentation/imgui/views/how_to_play/ImguiHowToPlayView.cpp
        src/application/presenters/HowToPlayPresenter.cpp
        include/application/presenters/HowToPlayPresenter.h
        include/presentation/imgui/views/how_to_play/ImguiHowToPlayView.h
        include/domain/UserStats.h
        include/interfaces/views/ISignInView.h
        include/interfaces/views/ISignUpView.h
        include/interfaces/views/IMainMenuView.h
        include/interfaces/views/IProfileView.h
        include/interfaces/views/ILeaderboardView.h
        include/interfaces/views/IHowToPlayView.h
        include/interfaces/views/game/ISudokuGameView.h
        include/interfaces/views/game/ISudokuGameDifficultySelectorView.h
        src/application/presenters/ProfilePresenter.cpp
        include/domain/sudoku/utils/SudokuFactory.h
        include/domain/sudoku/utils/SudokuLoader.h
        include/domain/sudoku/utils/SudokuSerializer.h
        src/domain/sudoku/utils/SudokuFactory.cpp
        src/domain/sudoku/utils/SudokuLoader.cpp
        src/domain/sudoku/utils/SudokuSerializer.cpp
        include/application/presenters/game/SudokuGameSummaryPresenter.h
        include/interfaces/views/game/ISudokuGameSummaryView.h
        src/presentation/imgui/views/game/ImguiSudokuGameSummaryView.cpp
        src/application/presenters/game/SudokuGameSummaryPresenter.cpp
        include/presentation/imgui/views/game/ImguiSudokuGameSummaryView.h
        src/presentation/imgui/managers/ImguiAudioManager.cpp
        include/presentation/imgui/managers/ImguiAudioManager.h
        src/infrastructure/database/PostgreSQL/repositories/PostgreSQLRepositoryFactory.cpp
        include/infrastructure/database/PostgreSQL/factories/PostgreSQLRepositoryFactory.h
        include/interfaces/database/repositories/IRepositoryFactory.h
        include/presentation/imgui/views/ImguiViewFactory.h
        include/factories/ViewFactory.h
        include/domain/custom_types/vector/DokuVector.h
        include/domain/custom_types/vector/DokuVectorIterator.h
        include/domain/custom_types/stack/DokuStack.h
)

target_include_directories(XDoku PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        deps/glad/glad-4-3/include
        deps/imgui
        deps/imgui/backends
        deps/nlohmann_json
        deps/stb
        deps/miniaudio
        deps/bcrypt/include
)

if (NOT WIN32)
    # Nothing in the codebase includes a bare "bcrypt.h" (only "bcrypt/bcrypt.h", already
    # reachable via deps/bcrypt/include above), so this extra path is unnecessary. On
    # Windows it's actively harmful: the Windows SDK's own CNG header is also named
    # bcrypt.h, and this directory being earlier on the search path shadows it, breaking
    # any system header (e.g. wincrypt.h) that expects the real one.
    target_include_directories(XDoku PRIVATE deps/bcrypt/include/bcrypt)
endif ()

if (NOT WIN32)
    target_sources(XDoku PRIVATE deps/bcrypt/src/x86.S)
endif ()

# Some libpqxx/libpq installs (e.g. Homebrew's config-mode packages) only
# export modern imported targets ("libpqxx::pqxx", "PostgreSQL::PostgreSQL"),
# which is also what carries the include directories. Others (older distro
# packages) just expose plain "pqxx"/"pq" libraries on the linker path with
# headers in a default system include dir. Prefer the modern targets when
# they exist, fall back otherwise.
if (TARGET libpqxx::pqxx)
    set(PQXX_TARGET libpqxx::pqxx)
else ()
    set(PQXX_TARGET pqxx)
endif ()

if (TARGET PostgreSQL::PostgreSQL)
    set(PQ_TARGET PostgreSQL::PostgreSQL)
else ()
    set(PQ_TARGET pq)
endif ()

target_link_libraries(XDoku PRIVATE
        ${PQXX_TARGET}
        ${PQ_TARGET}
        glfw
        OpenGL::GL
)

if (NOT WIN32)
    # Thread support is part of the CRT on Windows; there's no separate pthread
    # library to link against there (and vcpkg doesn't ship one for MSVC).
    target_link_libraries(XDoku PRIVATE pthread)
endif ()

# HardwareId's platform-specific backends need extra system libraries.
if (APPLE)
    target_link_libraries(XDoku PRIVATE "-framework IOKit" "-framework CoreFoundation")
elseif (WIN32)
    target_link_libraries(XDoku PRIVATE advapi32)
endif ()
