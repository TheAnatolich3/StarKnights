#ifndef PARTICLEBUFFER_HPP
#define PARTICLEBUFFER_HPP

#include <Utils/GeneralUtils.hpp> 
#include <VertexBuffer.hpp>

class ParticleBuffer : public VertexBuffer
{
public:
    struct ParticleData
    {
        glm::vec2 pos;
        glm::vec2 velocity;
        utils::color color = glm::vec4{ 1.0 };
        float phase = 0;
    };

    virtual void addData(ParticleData data) = 0;

    virtual ~ParticleBuffer() = default;
};


#endif PARTICLEBUFFER_HPP