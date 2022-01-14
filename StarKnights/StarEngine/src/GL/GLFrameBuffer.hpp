#ifndef GLFRAMEBUFFER_HPP
#define GLFRAMEBUFFER_HPP

#include <Framebuffer.hpp>
#include <glm/glm.hpp>

class Engine;

class GLFrameBuffer final : public FrameBuffer
{
public:
    explicit GLFrameBuffer(const Engine& engine, glm::vec2 size);
    void drawToFrameBuffer(std::function<void(void)> callback) override;

    virtual ~GLFrameBuffer();

private:
    uint32_t _fbo;
};


#endif GLFRAMEBUFFER_HPP