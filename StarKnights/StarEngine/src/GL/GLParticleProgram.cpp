#include <Engine.hpp>
#include <FileManager.hpp>
#include "GLParticleProgram.hpp"

GLParticleProgram::GLParticleProgram(const Engine& engine)
	: GLProgram(
		engine.fileManager().resourceLocation("particle_vertex_shader.vert"),
		engine.fileManager().resourceLocation("particle_frag_shader.vert"))
{ }