#include <GL/glew.h>
#include <Bitmap.hpp>
#include "GLTexture.hpp"

GLTexture::GLTexture(Bitmap bitmap)
	: Texture(bitmap.getSize())
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	int ch = bitmap.getColorCountChannels();
	const auto internal_format = [&]()
	{
		switch (ch)
		{
		case 1: return GL_R8;
		case 2: return GL_RG;
		case 3: return GL_RGB;
		case 4: return GL_RGBA;
		}
	}();

	const auto format = [&]()
	{
		switch (ch)
		{
		case 1: return GL_RED;
		case 2: return GL_RG;
		case 3: return GL_RGB;
		case 4: return GL_RGBA;
		}
	}();

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, bitmap.getSize().x, bitmap.getSize().y, 0,
		format, GL_UNSIGNED_BYTE, bitmap.getImage().size() == 0 ? nullptr : bitmap.getImage().data());


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (bitmap.getImage().size() != 0)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}

void GLTexture::active()
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

uint32_t GLTexture::getId() const
{
	return _id;
}
