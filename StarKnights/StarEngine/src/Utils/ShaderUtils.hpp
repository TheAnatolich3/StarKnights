#ifndef SHADER_UTILS_HPP
#define SHADER_UTILS_HPP
#include <string>
#include <fstream>
#include <string_view>

std::string read_shader(const std::string_view file_name)
{
	std::string line, text;
	std::ifstream in(file_name.data());

	if (in.is_open())
	{
		while (!in.eof())
		{
			getline(in, line);
			text += line;
			text += '\n';
		}
	}
	in.close();
	return text;
}

#endif SHADER_UTILS_HPP