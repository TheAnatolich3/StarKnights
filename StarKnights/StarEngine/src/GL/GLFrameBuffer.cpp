#include <GL/GLTexture.hpp>
#include <Engine.hpp>
#include <Renderer.hpp>
#include <GL/GLHeaders.hpp>
#include <Bitmap.hpp>
#include "GLFrameBuffer.hpp"


GLFrameBuffer::GLFrameBuffer(const Engine& engine, glm::vec2 size)
{
    GLint curFBO;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &curFBO);

    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    _texture = engine.renderer().createTexture(Bitmap{ 4, std::vector <unsigned char>(NULL), size });
    auto glTexture = std::static_pointer_cast<GLTexture>(_texture);

    glTexture->active();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, glTexture->getId(), 0);

    glBindFramebuffer(GL_FRAMEBUFFER, curFBO);
}

GLFrameBuffer::~GLFrameBuffer()
{
    glDeleteFramebuffers(1, &_fbo);
}

void GLFrameBuffer::drawToFrameBuffer(std::function<void(void)> callback)
{
    GLint curFBO;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &curFBO);

    GLint curViewport[4];
    glGetIntegerv(GL_VIEWPORT, curViewport);

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    glDisable(GL_SCISSOR_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, _texture->getSize().x, _texture->getSize().y);
    glEnable(GL_SCISSOR_TEST);

    callback();

    glBindFramebuffer(GL_FRAMEBUFFER, curFBO);
    glViewport(curViewport[0], curViewport[1], curViewport[2], curViewport[3]);
}