﻿# CMakeList.txt: проект CMake для StarKnights; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
set(GAME_SRC "Launcher.cpp" 
            "Game/Earth.hpp" 
            "Game/Earth.cpp" 
            "Game/Tank.hpp" 
            "Game/Tank.cpp" 
            "Game/AudioMenu.hpp" 
            "Game/AudioMenu.cpp" 
            "Game/UserMenu.hpp" 
            "Game/UserMenu.cpp")
if(ANDROID)
    add_library (StarKnights SHARED ${GAME_SRC})
else()
    add_executable(StarKnights ${GAME_SRC})
endif()

set_target_properties(StarKnights PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_subdirectory(StarEngine)

target_link_libraries(StarKnights StarEngine)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
