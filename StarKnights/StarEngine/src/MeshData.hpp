#ifndef MESHDATA_HPP
#define MESHDATA_HPP

#include <vector>
#include <glm/glm.hpp>
#include <Utils/GeneralUtils.hpp>

class MeshData
{
public:
	struct Vertex
	{
		glm::vec2 position;
		glm::vec2 texcoord;
		utils::color color{ glm::vec4(1) };
	};

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indexes;
};

#endif MESHDATA_HPP
