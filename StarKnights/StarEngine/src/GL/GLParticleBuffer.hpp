#ifndef GLPARTICLEBUFFER_HPP
#define GLPARTICLEBUFFER_HPP

#include <ParticleBuffer.hpp>
#include <vector>

class GLParticleBuffer : public ParticleBuffer
{
public:
    explicit GLParticleBuffer(std::vector<ParticleData> data);

    explicit GLParticleBuffer(uint32_t capacity);
    void addData(ParticleData data) override;

    virtual ~GLParticleBuffer();

    void draw();

private:
    uint32_t _VAO = 0;
    uint32_t _VBO = 0;

    uint32_t _count;

    bool _isDynamic = false;
    uint32_t _capacity = 0;
    uint32_t _curPos = 0;

    void createBuffers();
    void createLayouts();
};

#endif GLPARTICLEBUFFER_HPP