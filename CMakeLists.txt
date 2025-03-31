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
        include/core/IView.h
        include/core/IPresenter.h
        include/models/User.h
        include/models/SudokuGrid.h
        include/core/database/IDatabase.h
        include/models/database/PostgreSQL/PostgreSQLDatabase.h
        include/views/MenuView.h
        include/views/AuthView.h
        include/views/GameView.h
        include/views/ProfileView.h
        include/views/LeaderboardView.h
        include/presenters/AuthPresenter.h
        include/presenters/GamePresenter.h
        include/presenters/LeaderboardPresenter.h
        include/presenters/MenuPresenter.h
        include/presenters/ProfilePresenter.h
        src/models/database/PostgreSQL/PostgreSQLDatabase.cpp
        include/models/database/PostgreSQL/PostgreSQLDatabase.h
        include/core/database/IRepository.h
        include/models/database/PostgreSQL/repositories/UserRepository.h
        include/core/database/repositories/IUserRepository.h
        src/models/database/PostgreSQL/repositories/UserRepository.cpp
        include/core/database/iQuery.h
        include/core/database/iQuery.h
        src/models/database/PostgreSQL/PostgreSQLQuery.cpp
        include/models/database/PostgreSQL/PostgreSQLQuery.h
)

target_include_directories(XDoku PRIVATE
        deps/glad/glad-4-3/include
)

target_link_libraries(XDoku PRIVATE
        pqxx
        pq
        glfw
        OpenGL::GL
        pthread
)
