#include <Bitmap.hpp>
#include <Engine.hpp>
#include <Renderer.hpp>
#include <Window.hpp>
#include <ShaderProgram.hpp>
#include <MeshData.hpp>

#include "PhysicsSprite.hpp"

PhysicsSprite::PhysicsSprite(const Engine& engine, std::string_view filepath)
    : Node(engine)
{
    Bitmap bitmap(engine, filepath);

    _contentSize = bitmap.getSize();

    MeshData data;

    data.vertices.emplace_back();
    data.vertices.back().position = { 0.0, 0.0 };
    data.vertices.back().texcoord = { 0.0, 0.0 };

    data.vertices.emplace_back();
    data.vertices.back().position = { 0.0, bitmap.getSize().y };
    data.vertices.back().texcoord = { 0.0, 1.0 };

    data.vertices.emplace_back();
    data.vertices.back().position = { bitmap.getSize().x, bitmap.getSize().y };
    data.vertices.back().texcoord = { 1.0, 1.0 };

    data.vertices.emplace_back();
    data.vertices.back().position = { bitmap.getSize().x, 0.0 };
    data.vertices.back().texcoord = { 1.0, 0.0 };

    data.indexes.emplace_back(0);
    data.indexes.emplace_back(2);
    data.indexes.emplace_back(3);

    data.indexes.emplace_back(0);
    data.indexes.emplace_back(1);
    data.indexes.emplace_back(2);

    _command.vertexBuffer = engine.renderer().createVertexBuffer(std::move(data));
    _command.program = engine.renderer().createProgram("draw");

    _textureUniform = _command.program->createTextureUniform("uTexture");
    _textureUniform->texture = engine.renderer().createTexture(std::move(bitmap));

    _screenSizeUniform = _command.program->createVec2Uniform("uScreenSize");
    _transformUniform = _command.program->createMat3Uniform("uTransform");

    _command.uniforms.push_back(_transformUniform);
    _command.uniforms.push_back(_screenSizeUniform);
    _command.uniforms.push_back(_textureUniform);
}

void PhysicsSprite::visitSelf()
{
    const auto& win = _engine.window();
    _screenSizeUniform->value.x = win.getWidth();
    _screenSizeUniform->value.y = win.getHeight();

    _transformUniform->value = this->getTransform();

    _command.mask = _renderMask;

    _engine.renderer().addCommand(_command);
}