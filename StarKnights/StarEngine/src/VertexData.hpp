#ifndef VERTEXDATA_HPP
#define VERTEXDATA_HPP

#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <Utils/CppExt.hpp>

struct VertexLayout
{
    enum Type
    {
        Float, Vec2, Vec3, Vec4, Color
    } type{};
    bool normalized{};
};

struct VertexData
{
    virtual const void* data() const = 0;
    virtual size_t dataSize() const = 0;
    virtual size_t vertexSize() const = 0;

    virtual VertexLayout layoutFor(size_t index) const = 0;
    virtual size_t offsetFor(size_t index) const = 0;
    virtual size_t componentsNum() const = 0;

    ext::array_view<uint32_t> indexes;
};

#endif VERTEXDATA_HPP