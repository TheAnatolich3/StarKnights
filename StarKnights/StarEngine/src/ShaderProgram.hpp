#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <memory>
#include <vector>
#include <string_view>
#include <glm/glm.hpp>
#include <functional>

class Texture;

class Uniform
{
public:
    std::function<void(void)> onActivate;

    virtual void activate()
    {
        if (onActivate)
        {
            onActivate();
        }
    }
    virtual ~Uniform() = default;
};

class TextureUniform : public Uniform
{
public:
    std::shared_ptr<Texture> texture;
    virtual void activateWithSlot(size_t slot) = 0;
};

class Mat3Uniform : public Uniform
{
public:
    glm::mat3 value;
};

class Vec2Uniform : public Uniform
{
public:
    glm::vec2 value;
};

class Vec3Uniform : public Uniform
{
public:
    glm::vec3 value;
};

class FloatUniform : public Uniform
{
public:
    float value;
};

class ShaderProgram : public std::enable_shared_from_this<ShaderProgram>
{
public:
    virtual ~ShaderProgram() = default;
    virtual void activate() = 0;

    virtual std::shared_ptr<TextureUniform> createTextureUniform(std::string_view name) = 0;
    virtual std::shared_ptr<Mat3Uniform> createMat3Uniform(std::string_view name) = 0;
    virtual std::shared_ptr<Vec2Uniform> createVec2Uniform(std::string_view name) = 0;
    virtual std::shared_ptr<Vec3Uniform> createVec3Uniform(std::string_view name) = 0;
    virtual std::shared_ptr<FloatUniform> createFloatUniform(std::string_view name) = 0;
};

#endif SHADERPROGRAM_HPP