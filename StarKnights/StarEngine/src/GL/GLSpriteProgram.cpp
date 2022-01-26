#include <Engine.hpp>
#include <FileManager.hpp>
#include "GLSpriteProgram.hpp"

GLSpriteProgram::GLSpriteProgram(const Engine& engine)
	: GLProgram(
		engine.fileManager().resourceLocation("sprite_vertex_shader.vert"),
		engine.fileManager().resourceLocation("sprite_frag_shader.vert"))
{ }