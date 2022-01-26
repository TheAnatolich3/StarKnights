#include <Engine.hpp>
#include <FileManager.hpp>
#include "GLBlurProgram.hpp"

GLBlurProgram::GLBlurProgram(const Engine& engine)
	: GLProgram(
		engine.fileManager().resourceLocation("blur_vertex_shader.vert"),
		engine.fileManager().resourceLocation("blur_frag_shader.vert"))
{ }