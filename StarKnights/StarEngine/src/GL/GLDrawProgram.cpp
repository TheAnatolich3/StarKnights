#include <GeneralUtils.hpp>
#include "GLDrawProgram.hpp"


GLDrawProgram::GLDrawProgram()
	: GLProgram(utils::read_file("../../../../GalaxyBattles/EtanolEngine/src/shader.vert"),
		utils::read_file("../../../../GalaxyBattles/EtanolEngine/src/frag_shader.vert"))
{

}