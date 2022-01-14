#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <string_view>
#include <vector>
#include <glm/glm.hpp>

class Bitmap
{
public:
	explicit Bitmap(std::string_view filepath);
	explicit Bitmap(int count_channels, std::vector<unsigned char> data, glm::vec2 size);
	[[nodiscard]] const std::vector<unsigned char>& getImage() const;

	[[nodiscard]] int getColorCountChannels() const;
	[[nodiscard]] glm::vec2 getSize() const;

private:
	int _cnt_color_channels;
	std::vector<unsigned char> _image;
	glm::vec2 _size;
};

#endif BITMAP_HPP