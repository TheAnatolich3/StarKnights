#include "GLParticleProgram.hpp"

GLParticleProgram::GLParticleProgram()
	: GLProgram(
		"../../../../StarKnights/StarEngine/src/Shaders/particle_vertex_shader.vert",
		"../../../../StarKnights/StarEngine/src/Shaders/particle_frag_shader.vert")
{ }