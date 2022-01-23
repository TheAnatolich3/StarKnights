#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP
#include <Renderer.hpp>
#include <unordered_map>
#include <string>

class SDL_Window;
class Engine;
class FrameBuffer;
class TextureUniform;
class Vec2Uniform;
class Vec3Uniform;
class FloatUniform;
class GLVertexBuffer;

class GLRenderer : public Renderer
{
public:
	explicit GLRenderer(const Engine& engine, SDL_Window* window);

	void init() override;
	void draw() override;

	std::shared_ptr<VertexBuffer> createVertexBuffer(MeshData data) const override;
	//TODO: createVertexBuffer (vertexData)
	std::shared_ptr<ShaderProgram> createProgram(std::string_view name) const override;

	std::shared_ptr<ParticleBuffer> createParticleBuffer(std::vector<ParticleBuffer::ParticleData> data) const override;
	std::shared_ptr<ParticleBuffer> createParticleBuffer(size_t count) const override;

	std::shared_ptr<Texture> createTexture(Bitmap bitmap) const override;

	glm::vec2 getRenderResolution() const override;
private:
	const Engine& _engine;
	std::unique_ptr<void, void(*)(void*)> _drawContext;

	mutable std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> _programs;

	std::shared_ptr<ShaderProgram> _ppProgram;
	std::shared_ptr<ShaderProgram> _blurProgram;

	std::shared_ptr<FrameBuffer> _origFbo;
	std::shared_ptr<FrameBuffer> _bloomFbo;
	std::shared_ptr<FrameBuffer> _blurFbo;

	std::shared_ptr<TextureUniform>  _textureUniform;
	std::shared_ptr<TextureUniform>  _texture2Uniform;
	std::shared_ptr<Vec3Uniform>  _distortUniform;
	std::shared_ptr<FloatUniform>  _timeUniform;

	std::shared_ptr<GLVertexBuffer>  _buffer;

	std::shared_ptr<TextureUniform>  _blurTextureUniform;
	std::shared_ptr<Vec2Uniform>  _blurRadUniform;
};
#endif