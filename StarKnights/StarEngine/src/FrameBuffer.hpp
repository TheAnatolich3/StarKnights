#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <memory>
#include <functional>

class Texture;
class FrameBuffer
{
public:
    virtual ~FrameBuffer() = default;
    std::shared_ptr<Texture> getTexture() const;

    virtual void drawToFrameBuffer(std::function<void(void)> callback) = 0;

protected:
    std::shared_ptr<Texture> _texture;
};


#endif FRAMEBUFFER_HPP