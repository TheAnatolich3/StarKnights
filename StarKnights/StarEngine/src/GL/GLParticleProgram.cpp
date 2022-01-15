#include <Utils/ShaderUtils.hpp>
#include "GLParticleProgram.hpp"

GLParticleProgram::GLParticleProgram()
	: GLProgram(read_shader("../../../../StarKnights/StarEngine/src/Shaders/particle_vertex_shader.vert"),
		read_shader("../../../../StarKnights/StarEngine/src/Shaders/particle_frag_shader.vert"))
{

}