#include <Engine.hpp>
#include <FileManager.hpp>
#include "GLPpProgram.hpp"

GLPpProgram::GLPpProgram(const Engine& engine)
	: GLProgram(
		engine.fileManager().resourceLocation("pp_vertex_shader.vert"),
		engine.fileManager().resourceLocation("pp_frag_shader.vert"))
{}