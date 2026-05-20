cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject src/main.cpp
        src/GamePlay.cpp
        src/GamePlay.h
        src/Player.cpp
        src/Player.h
        src/DeltaTime.cpp
        src/DeltaTime.h
        src/Map.cpp
        src/Map.h
        src/Entities.cpp
        src/Entities.h
        src/Menu.cpp
        src/Menu.h
        src/Door.cpp
        src/Door.h
        src/Rhaegal.cpp
        src/Rhaegal.h
        src/Pnj.cpp
        src/Pnj.h
        src/RenderText.cpp
        src/RenderText.h
        src/Fight.cpp
        src/Fight.h
        src/Monster.cpp
        src/Monster.h
        src/GiantParrot.cpp
        src/GiantParrot.h
        src/Snake.cpp
        src/Snake.h
        src/Tarrasque.cpp
        src/Tarrasque.h
        src/Audio.cpp
        src/Audio.h
)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-audio)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
