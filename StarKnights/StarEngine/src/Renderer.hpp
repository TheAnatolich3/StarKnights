#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <optional>
#include <memory>
#include <string_view>
#include <glm/glm.hpp>
#include <ParticleBuffer.hpp>

class VertexBuffer;
class ShaderProgram;
class Texture;
class Uniform;
class Bitmap;
class MeshData;

class Renderer
{
public:
    virtual ~Renderer() = default;
    virtual void init() = 0;

    struct Command
    {
        uint32_t mask;
        std::shared_ptr<VertexBuffer> vertexBuffer;
        std::shared_ptr<ShaderProgram> program;
        std::vector<std::shared_ptr<Uniform>> uniforms;

        std::optional<glm::vec4> scissor;

        struct sub_t
        {
            int count = 0;
            int offset = 0;
        };

        std::optional<sub_t> ren;
    };

    void addCommand(Command command) const
    {
        _commands.push_back(std::move(command));
    }

    virtual void draw() = 0;

    virtual std::shared_ptr<VertexBuffer> createVertexBuffer(MeshData data) const = 0;
    virtual std::shared_ptr<ParticleBuffer> createParticleBuffer(std::vector<ParticleBuffer::ParticleData> data) const = 0;
    virtual std::shared_ptr<ParticleBuffer> createParticleBuffer(size_t count) const = 0;

    virtual std::shared_ptr<ShaderProgram> createProgram(std::string_view name) const = 0;
    virtual std::shared_ptr<Texture> createTexture(Bitmap bitmap) const = 0;

    mutable glm::vec3 _distortCoord;

    virtual glm::vec2 getRenderResolution() const = 0;
protected:
    mutable std::vector<Command> _commands;
};

#endif RENDERER_HPP
