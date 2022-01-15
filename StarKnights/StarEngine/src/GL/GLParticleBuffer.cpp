#include <GL/glew.h>
#include "GlParticleBuffer.hpp"


GLParticleBuffer::GLParticleBuffer(std::vector<ParticleData> data)
{
    this->createBuffers();

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(ParticleData), data.data(), GL_STATIC_DRAW);

    this->createLayouts();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    _count = static_cast<uint32_t>(data.size());
}

GLParticleBuffer::GLParticleBuffer(uint32_t capacity)
{
    this->createBuffers();

    glBufferData(GL_ARRAY_BUFFER, capacity * sizeof(ParticleData), nullptr, GL_STREAM_DRAW);

    this->createLayouts();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    _count = 0;
    _curPos = 0;
    _capacity = capacity;

    _isDynamic = true;
}

void GLParticleBuffer::draw()
{
    if (_count > 0)
    {
        glBindVertexArray(_VAO);
        glDrawArrays(GL_POINTS, 0, _count);
    }
}

void GLParticleBuffer::createBuffers()
{
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
}

void GLParticleBuffer::createLayouts()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,
        GL_FLOAT, GL_FALSE, sizeof(ParticleData), reinterpret_cast<void*>(offsetof(ParticleData, pos)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2,
        GL_FLOAT, GL_FALSE, sizeof(ParticleData), reinterpret_cast<void*>(offsetof(ParticleData, velocity)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4,
        GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ParticleData), reinterpret_cast<void*>(offsetof(ParticleData, color)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1,
        GL_FLOAT, GL_FALSE, sizeof(ParticleData), reinterpret_cast<void*>(offsetof(ParticleData, phase)));
}

void GLParticleBuffer::addData(ParticleData data)
{
    if (!_isDynamic)
    {
        throw std::logic_error("Can't update static buffer!");
    }

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferSubData(GL_ARRAY_BUFFER, _curPos * sizeof(ParticleData), sizeof(ParticleData), &data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    ++_curPos;

    if (_count < _capacity)
    {
        ++_count;
    }

    _curPos %= _capacity;
}

GLParticleBuffer::~GLParticleBuffer()
{
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);
}