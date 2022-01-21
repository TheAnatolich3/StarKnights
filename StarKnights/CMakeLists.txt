# CMakeList.txt: проект CMake для StarKnights; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (StarKnights "Launcher.cpp" 
                            "Game/Earth.hpp" 
                            "Game/Earth.cpp")

set_target_properties(StarKnights PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_subdirectory(StarEngine)

target_link_libraries(StarKnights StarEngine)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
