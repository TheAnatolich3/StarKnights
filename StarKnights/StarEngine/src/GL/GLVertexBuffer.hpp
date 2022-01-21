#ifndef GLVERTEXBUFFER_HPP
#define GLVERTEXBUFFER_HPP

#include <VertexBuffer.hpp>

class Engine;
class MeshData;

class GLVertexBuffer final : public VertexBuffer
{
public:
    explicit GLVertexBuffer(const Engine& engine, MeshData data);

    virtual ~GLVertexBuffer();

    void draw(size_t count, size_t pos);
    void draw();
private:
    uint32_t _VAO = -1;
    uint32_t _VBO = -1;
    uint32_t _IBO = -1;

    uint32_t _count;

    const Engine& _engine;
};

#endif GLVERTEXBUFFER_HPP