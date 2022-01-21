#include <GL/glew.h>
#include <MeshData.hpp>
#include <Engine.hpp>
#include <Renderer.hpp>
#include "GLVertexBuffer.hpp"

GLVertexBuffer::GLVertexBuffer(const Engine& engine, MeshData data) : _engine(engine)
{
    glGenVertexArrays(1, &_VAO);

    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(MeshData::Vertex), data.vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2,
        GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), reinterpret_cast<void*>(offsetof(MeshData::Vertex, position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2,
        GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), reinterpret_cast<void*>(offsetof(MeshData::Vertex, texcoord)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4,
        GL_UNSIGNED_BYTE, GL_TRUE, sizeof(MeshData::Vertex), reinterpret_cast<void*>(offsetof(MeshData::Vertex, color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        data.indexes.size() * sizeof(std::uint32_t),
        data.indexes.data(), GL_STATIC_DRAW);

    _count = data.indexes.size();
}


void GLVertexBuffer::draw(size_t count, size_t pos)
{
    glBindVertexArray(_VAO);

    if (_IBO != -1)
    {
        glDrawElements(GL_TRIANGLES,
            static_cast<GLsizei>(count),
            GL_UNSIGNED_INT,
            reinterpret_cast<void*>(pos));
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, pos, count);
    }
}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers(1, &_VBO);
    if (_IBO != -1)
    {
        glDeleteBuffers(1, &_IBO);
    }
    
    glDeleteVertexArrays(1, &_VAO);
}

void GLVertexBuffer::draw()
{
    this->draw(_count, 0);
}
