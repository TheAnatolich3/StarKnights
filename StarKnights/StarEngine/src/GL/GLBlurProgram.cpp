#include "GLBlurProgram.hpp"

GLBlurProgram::GLBlurProgram()
	: GLProgram(
		"../../../../StarKnights/StarEngine/src/Shaders/blur_vertex_shader.vert",
		"../../../../StarKnights/StarEngine/src/Shaders/blur_frag_shader.vert")
{ }