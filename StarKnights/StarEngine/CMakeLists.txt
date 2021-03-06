set(CMAKE_CXX_STANDARD 17)

add_definitions(-DPROJECT_ROOT_FOLDER=${PROJECT_SOURCE_DIR})

add_library(StarEngine STATIC "src/Engine.hpp"
							  "src/Engine.cpp" 
							  "src/Texture.hpp" 
							  "src/Texture.cpp" 
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
							  "src/GL/GLSpriteProgram.hpp" 
							  "src/GL/GLSpriteProgram.cpp" 
							  "src/Node.hpp" 
							  "src/Node.cpp" 
							  "src/SchedulerManager.hpp" 
							  "src/SchedulerManager.cpp" 
							  "src/ActionManager.hpp" 
							  "src/ActionManager.cpp" 
							  "src/GL/GLBlurProgram.hpp" 
							  "src/GL/GLBlurProgram.cpp" 
							  "src/FrameBuffer.hpp" 
							  "src/FrameBuffer.cpp" 
							  "src/GL/GLFrameBuffer.hpp" 
							  "src/GL/GLFrameBuffer.cpp" 
							  "src/Utils/GeneralUtils.hpp" 
							  "src/GL/GLParticleBuffer.hpp" 
							  "src/GL/GLParticleBuffer.cpp" 
							  "src/ParticleBuffer.hpp" 
							  "src/ParticleBuffer.cpp" 
							  "src/GL/GLParticleProgram.hpp" 
							  "src/GL/GLParticleProgram.cpp" 
							  "src/GL/GLPpProgram.hpp" 
							  "src/GL/GLPpProgram.cpp" 
							  "src/VertexData.hpp" 
							  "src/Sprite.hpp" 
							  "src/Sprite.cpp" 
							  "src/PhysicsSprite.hpp" 
							  "src/PhysicsSprite.cpp" 
							  "src/Sound.hpp" 
							  "src/Sound.cpp" 
							  "src/AudioManager.hpp" 
							  "src/AudioManager.cpp" 
							  "src/Button.hpp" 
							  "src/Button.cpp" 
							  "src/UIManager.hpp" 
							  "src/UIManager.cpp" 
							  "src/MenuItem.hpp" 
							  "src/MenuItem.cpp" 
							  "src/TaskManager.hpp" 
							  "src/TaskManager.cpp"
							  "src/Utils/ResourceManager.hpp"
							  "src/FileManager.hpp" "src/FileManager.cpp" "src/GL/GLHeaders.hpp")

#SDL
if(NOT IOS)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2)
	set(SDL2MAIN_LIBRARY SDL2main)
	set(SDL2_LIBRARY SDL2-static)
endif()

if (MSVC)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glew)
	set(GLEW_LIBRARY libglew_static)

	target_link_libraries(StarEngine PRIVATE ${GLEW_LIBRARY})
    find_package(OpenGL REQUIRED)
else()
	find_library(OpenGL REQUIRED)
    target_link_libraries(StarEngine PRIVATE ${OPENGL_LIBRARY})
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)
set(IMGUI_LIBRARY imgui)

if (NOT ANDROID)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/box2d-main)
	set(BOX2D_LIBRARY box2d)

	target_link_libraries(StarEngine PUBLIC ${BOX2D_LIBRARY})
endif()

target_link_libraries(StarEngine PUBLIC
	${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY} ${IMGUI_LIBRARY})

target_include_directories(StarEngine
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/libs
		${CMAKE_CURRENT_SOURCE_DIR}/utils
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2/include
		${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)
