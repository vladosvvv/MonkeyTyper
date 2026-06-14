cmake_minimum_required(VERSION 3.30)
cmake_policy(VERSION 3.30)

project(2425L_11_s33262_ZJM)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        11.1.4
        GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(fmt)


FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.0.0
        GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(SFML)


add_executable(2425L_11_s33262_ZJM
        main.cpp
        game.cpp
        game.h
)



target_link_libraries(2425L_11_s33262_ZJM
        SFML::Graphics
        SFML::Window
        SFML::System
        fmt::fmt
)
