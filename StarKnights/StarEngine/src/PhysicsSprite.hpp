#ifndef PHYSICS_SPRITE_HPP
#define PHYSICS_SPRITE_HPP

#include <Node.hpp>
#include <string_view>
#include <Renderer.hpp>

class Engine;
class Texture;
class VertexBuffer;
class ShaderProgram;
class TextureUniform;
class Mat3Uniform;
class Vec2Uniform;
class b2Body;

class PhysicsSprite : public Node
{
public:
    explicit PhysicsSprite(const Engine& engine, std::string_view filepath);

protected:
    void visitSelf() override;

private:
    Renderer::Command _command;
    b2Body* _box;
    std::shared_ptr<Vec2Uniform> _screenSizeUniform;
    std::shared_ptr<Mat3Uniform>  _transformUniform;
    std::shared_ptr<TextureUniform>  _textureUniform;
};
#endif PHYSICS_SPRITE_HPP