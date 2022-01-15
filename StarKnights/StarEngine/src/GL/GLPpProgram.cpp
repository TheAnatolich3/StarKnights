#include <Utils/ShaderUtils.hpp>
#include "GLPpProgram.hpp"

GLPpProgram::GLPpProgram()
	: GLProgram(read_shader("../../../../StarKnights/StarEngine/src/Shaders/pp_vertex_shader.vert"),
		read_shader("../../../../StarKnights/StarEngine/src/Shaders/pp_frag_shader.vert"))
{

}