#include <Utils/ShaderUtils.hpp>
#include "GLDrawProgram.hpp"

GLDrawProgram::GLDrawProgram()
	: GLProgram(read_shader("../../../../GalaxyBattles/EtanolEngine/src/shader.vert"),
		read_shader("../../../../GalaxyBattles/EtanolEngine/src/frag_shader.vert"))
{

}