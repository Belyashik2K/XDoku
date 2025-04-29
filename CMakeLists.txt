cmake_minimum_required(VERSION 3.30)
project(XDoku)

set(CMAKE_CXX_STANDARD 26)

find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

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
        include/core/IView.h
        include/core/IPresenter.h
        include/models/User.h
        include/core/database/IDatabase.h
        include/models/database/PostgreSQL/PostgreSQLDatabase.h
        src/models/database/PostgreSQL/PostgreSQLDatabase.cpp
        include/models/database/PostgreSQL/PostgreSQLDatabase.h
        include/models/database/PostgreSQL/repositories/PostgreSQLUserRepository.h
        include/core/database/repositories/IUserRepository.h
        src/models/database/PostgreSQL/repositories/PostgreSQLUserRepository.cpp
        include/core/database/iQuery.h
        include/core/database/iQuery.h
        src/models/database/PostgreSQL/PostgreSQLQuery.cpp
        include/models/database/PostgreSQL/PostgreSQLQuery.h
        include/models/custom_types/Timestamp.h
        src/models/custom_types/Timestamp.cpp
        src/models/User.cpp
        include/utils.h
        src/utils.cpp
        include/core/database/repositories/IGameRepository.h
        include/core/database/repositories/IMoveRepository.h
        include/core/database/repositories/ISessionRepository.h
        include/core/database/repositories/IRatingRepository.h
        include/models/sudoku/SudokuGame.h
        include/models/sudoku/SudokuGrid.h
        include/models/sudoku/SudokuCell.h
        include/models/sudoku/enums/SudokuDifficulty.h
        include/models/sudoku/utils/SudokuGenerator.h
        include/models/sudoku/enums/SudokuGameStatus.h
        src/models/sudoku/enums/SudokuDifficulty.cpp
        src/models/sudoku/enums/SudokuGameStatus.cpp
        src/models/sudoku/utils/SudokuGenerator.cpp
        src/models/sudoku/SudokuCell.cpp
        src/models/sudoku/SudokuGrid.cpp
        src/tests/sudoku/generator.cpp
        include/tests/sudoku/generator.h
        src/models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.cpp
        include/models/database/PostgreSQL/repositories/PostgreSQLSessionRepository.h
        src/models/sudoku/SudokuGame.cpp
        include/models/database/PostgreSQL/repositories/PostgreSQLGameRepository.h
        src/models/database/PostgreSQL/repositories/PostgreSQLGameRepository.cpp
        include/models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.h
        src/models/database/PostgreSQL/repositories/PostgreSQLRatingRepository.cpp
        include/models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.h
        src/models/database/PostgreSQL/repositories/PostgreSQLMoveRepository.cpp
        include/models/leaderboard/LeaderboardPlace.h
        include/models/sudoku/SudokuMove.h
        src/models/sudoku/SudokuMove.cpp
        include/core/app_events/IEvent.h
        include/core/EventBus.h
        include/core/AppMediator.h
        include/core/Application.h
        src/EventBus.cpp
        src/AppMediator.cpp
        include/presenters/LoginPresenter.h
        include/views/imgui/login/ImguiLoginView.h
        include/views/imgui/ImguiView.h
        src/views/imgui/login/ImguiLoginView.cpp
        src/presenters/LoginPresenter.cpp
        include/core/IFrameHandler.h
        include/views/imgui/ImguiFrameHandler.h
        src/views/imgui/ImguiFrameHandler.cpp
        src/Application.cpp
        include/managers/TextureManager.h
        src/managers/TextureManager.cpp
        include/views/imgui/ImguiWindow.h
        include/views/imgui/ImguiChildWindow.h
        src/views/imgui/ImguiWindow.cpp
        src/views/imgui/ImguiChildWindow.cpp
        src/views/imgui/ImguiView.cpp
)

target_include_directories(XDoku PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        deps/glad/glad-4-3/include
        deps/imgui
        deps/imgui/backends
        deps/nlohmann_json
        deps/stb
)

target_link_libraries(XDoku PRIVATE
        pqxx
        pq
        glfw
        OpenGL::GL
        pthread
        bcrypt
        ncurses
)
