#include "FrameBuffer.hpp"

std::shared_ptr<Texture> FrameBuffer::getTexture() const
{
    return _texture;
}
