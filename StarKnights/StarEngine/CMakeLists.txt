set(CMAKE_CXX_STANDARD 17)

add_library(StarEngine STATIC "src/Engine.hpp"
							  "src/Engine.cpp" 
							  "src/Texture.hpp" 
							  "src/Texture.cpp" 
							  "utils/GeneralUtils.hpp" 
							  "src/VertexBuffer.hpp" 
							  "src/MeshData.hpp" 
							  "src/ShaderProgram.hpp" 
							  "src/Renderer.hpp" 
							  "src/Bitmap.hpp" 
							  "src/Bitmap.cpp" 
							  "src/SDL/SDLWindow.hpp" 
							  "src/SDL/SDLWindow.cpp" 
							  "src/Window.hpp" 
							  "src/EventsManager.hpp" 
							  "src/EventsManager.cpp" 
							  "src/GL/GLRenderer.hpp" 
							  "src/GL/GLRenderer.cpp" 
							  "src/GL/GLTexture.hpp" 
							  "src/GL/GLTexture.cpp" 
							  "src/GL/GLVertexBuffer.hpp" 
							  "src/GL/GLVertexBuffer.cpp" 
							  "src/GL/GLProgram.hpp" 
							  "src/GL/GLProgram.cpp" 
							  "src/GL/GLDrawProgram.hpp" 
							  "src/GL/GLDrawProgram.cpp" 
							  "src/Node.hpp" 
							  "src/Node.cpp" "src/SchedulerManager.hpp" "src/SchedulerManager.cpp" "src/ActionManager.hpp" "src/ActionManager.cpp" "src/GL/GLBlurProgram.hpp" "src/GL/GLBlurProgram.cpp" "src/FrameBuffer.hpp" "src/FrameBuffer.cpp" "src/GL/GLFrameBuffer.hpp" "src/GL/GLFrameBuffer.cpp")

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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/box2d-main)
set(BOX2D_LIBRARY box2d)

target_link_libraries(StarEngine PUBLIC
	${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${IMGUI_LIBRARY} ${BOX2D_LIBRARY})

find_package(OpenGL REQUIRED)

target_include_directories(StarEngine
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/libs
		${CMAKE_CURRENT_SOURCE_DIR}/utils
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
		${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)

set(SYSTEM_LIBS -mwindows ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})