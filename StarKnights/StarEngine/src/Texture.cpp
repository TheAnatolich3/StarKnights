#include "Texture.hpp"

Texture::Texture(glm::vec2 size)
    : _size(size)
{

}

glm::vec2 Texture::getSize() const
{
    return _size;
}
