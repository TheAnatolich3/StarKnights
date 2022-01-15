#include <Shaders/ShaderUtils.hpp>
#include "GLBlurProgram.hpp"

GLBlurProgram::GLBlurProgram()
	: GLProgram(read_shader("../../../../StarKnights/StarEngine/src/Shaders/blur_vertex_shader.vert"),
		read_shader("../../../../StarKnights/StarEngine/src/Shaders/blur_frag_shader.vert"))
{

}