add_library(StarEngine STATIC "src/Engine.hpp"
							  "src/Engine.cpp")

#SDL
if(NOT IOS)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)
	set(SDL2MAIN_LIBRARY SDL2main)
	set(SDL2_LIBRARY SDL2-static)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glew)
set(GLEW_LIBRARY libglew_static)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)
set(IMGUI_LIBRARY imgui)

target_link_libraries(StarEngine PUBLIC
	${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${IMGUI_LIBRARY})

find_package(OpenGL REQUIRED)

target_include_directories(StarEngine
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/libs
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
		${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)

set(SYSTEM_LIBS -mwindows ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})