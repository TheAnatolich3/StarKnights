#include <stdexcept>
#include <string_view>

#include <Window.hpp>
#include <Bitmap.hpp>
#include <Engine.hpp>
#include <MeshData.hpp>
#include <SchedulerManager.hpp>

#include <SDL.h>
#include <GL/glew.h>

#include <GL/GLTexture.hpp>
#include <GL/GLPpProgram.hpp>
#include <GL/GLBlurProgram.hpp>
#include <GL/GLFrameBuffer.hpp>
#include <GL/GLSpriteProgram.hpp>
#include <GL/GLParticleProgram.hpp>
#include <GL/GLVertexBuffer.hpp>
#include <GL/GLParticleBuffer.hpp>

#include "GLRenderer.hpp"

GLRenderer::GLRenderer(const Engine& engine, SDL_Window* window)
	: _engine(engine)
	, _drawContext{ SDL_GL_CreateContext(window), SDL_GL_DeleteContext }
{
	printf("OpenGL version supported by this platform (%s): \n",
		glGetString(GL_VERSION));

	glDisable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewExperimental = GL_TRUE;
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		throw std::runtime_error("Glew error");
	}

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void GLRenderer::init()
{
	_ppProgram = std::make_shared<GLPpProgram>();
	_blurProgram = std::make_shared<GLBlurProgram>();

	_origFbo = std::make_shared<GLFrameBuffer>(_engine, glm::vec2(_engine.window().getWidth(), _engine.window().getHeight()));
	_bloomFbo = std::make_shared<GLFrameBuffer>(_engine, 0.25f * glm::vec2(_engine.window().getWidth(), _engine.window().getHeight()));
	_blurFbo = std::make_shared<GLFrameBuffer>(_engine, 0.25f * glm::vec2(_engine.window().getWidth(), _engine.window().getHeight()));

	_blurTextureUniform = _blurProgram->createTextureUniform("uTexture");
	_blurRadUniform = _blurProgram->createVec2Uniform("uDir");

	_textureUniform = _ppProgram->createTextureUniform("uTexture");
	_texture2Uniform = _ppProgram->createTextureUniform("uTexture2");
	_distortUniform = _ppProgram->createVec3Uniform("distortCoord");
	_timeUniform = _ppProgram->createFloatUniform("uTime");

	_timeUniform->value = 0;
	_textureUniform->texture = _origFbo->getTexture();
	_texture2Uniform->texture = _bloomFbo->getTexture();

	_blurTextureUniform->texture = _bloomFbo->getTexture();

	_distortCoord = glm::vec3{ 0.0f, 0.0f, 0.00001f };

	MeshData meshData;

	meshData.vertices.emplace_back();
	meshData.vertices.back().position = { -1.0, -1.0 };

	meshData.vertices.emplace_back();
	meshData.vertices.back().position = { -1.0, 1.0 };

	meshData.vertices.emplace_back();
	meshData.vertices.back().position = { 1.0, 1.0 };

	meshData.vertices.emplace_back();
	meshData.vertices.back().position = { 1.0, -1.0 };

	meshData.indexes.emplace_back(0);
	meshData.indexes.emplace_back(1);
	meshData.indexes.emplace_back(2);

	meshData.indexes.emplace_back(0);
	meshData.indexes.emplace_back(2);
	meshData.indexes.emplace_back(3);

	_buffer = std::make_shared<GLVertexBuffer>(_engine, meshData);
}

void GLRenderer::draw()
{
	auto needRender = [](uint32_t renderMask, uint32_t nodeMask)
	{
		return (renderMask == nodeMask) || (nodeMask & renderMask) != 0;
	};

	auto drawRenderCommand = [&](Command command)
	{
		auto glVertexBuffer = std::dynamic_pointer_cast<GLVertexBuffer>(
			command.vertexBuffer);
		auto glParticleBuffer = std::dynamic_pointer_cast<GLParticleBuffer>(
			command.vertexBuffer);

		if (glVertexBuffer || glParticleBuffer)
		{
			auto glProgram = std::dynamic_pointer_cast<GLProgram>(command.program);
			if (glProgram)
			{
				glProgram->activate();
				for (const auto& uniform : command.uniforms)
				{
					uniform->activate();
				}

				if (command.scissor)
				{
					glScissor((int)command.scissor->x,
						(int)(_engine.window().getHeight() - command.scissor->w),
						(int)(command.scissor->z - command.scissor->x),
						(int)(command.scissor->w - command.scissor->y));
				}
				else
				{
					glScissor(0, 0, _engine.window().getWidth(),
						_engine.window().getHeight());
				}

				if (glVertexBuffer)
				{
					if (command.ren)
					{
						glVertexBuffer->draw(command.ren->count, command.ren->offset);
					}
					else
					{
						glVertexBuffer->draw();
					}
				}
				if (glParticleBuffer)
				{
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);
					glParticleBuffer->draw();
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
			}
		}
	};


	_origFbo->drawToFrameBuffer([&]
		{
			glEnable(GL_BLEND);
			for (const auto& command : _commands)
			{
				drawRenderCommand(command);
			}
		}
	);

	_bloomFbo->drawToFrameBuffer([&]
		{
			glEnable(GL_BLEND);
			for (const auto& command : _commands)
			{
				if (needRender(0x1, command.mask))
				{
					drawRenderCommand(command);
				}
			}
		}
	);

	_commands.clear();

	_blurTextureUniform->texture = _bloomFbo->getTexture();

	_blurRadUniform->value = glm::vec2(4.0f / (float)_engine.window().getWidth(), 0.0);

	_blurFbo->drawToFrameBuffer([&]
		{
			_blurProgram->activate();
			_blurRadUniform->activate();
			_blurTextureUniform->activate();
			_buffer->draw();
		});

	_blurTextureUniform->texture = _blurFbo->getTexture();
	_blurRadUniform->value = glm::vec2(0.0, 4.0f / (float)_engine.window().getHeight());

	_bloomFbo->drawToFrameBuffer([&]()
		{
			_blurProgram->activate();
			_blurRadUniform->activate();
			_blurTextureUniform->activate();
			_buffer->draw();
		});

	glDisable(GL_SCISSOR_TEST);
	glDisable(GL_BLEND);

	glClearColor(0.0f, 0.3f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_distortUniform->value = _distortCoord;
	_timeUniform->value += _engine.schedulerManager().getCurrentDelta().count();

	_ppProgram->activate();
	_distortUniform->activate();
	_timeUniform->activate();
	_textureUniform->activateWithSlot(0);
	_texture2Uniform->activateWithSlot(1);
	_buffer->draw();
}


std::shared_ptr<VertexBuffer> GLRenderer::createVertexBuffer(MeshData data) const
{
	return std::make_shared<GLVertexBuffer>(_engine, data);
}

std::shared_ptr<ShaderProgram> GLRenderer::createProgram(std::string_view name) const
{
	std::string name_string(name);
	if (_programs.count(name_string) > 0)
	{
		return _programs[name_string];
	}
	std::shared_ptr<ShaderProgram> program = nullptr;
	if (name == "draw")
	{
		program = std::make_shared<GLSpriteProgram>();
	}
	else if (name == "particles")
	{
		program = std::make_shared<GLParticleProgram>();
	}

	_programs[name_string] = program;
	return program;
}

std::shared_ptr<Texture> GLRenderer::createTexture(Bitmap bitmap) const
{
	return std::make_shared<GLTexture>(std::move(bitmap));
}

std::shared_ptr<ParticleBuffer> GLRenderer::createParticleBuffer(std::vector<ParticleBuffer::ParticleData> data) const
{
	return std::make_shared<GLParticleBuffer>(std::move(data));
}

std::shared_ptr<ParticleBuffer> GLRenderer::createParticleBuffer(size_t count) const
{
	return std::make_shared<GLParticleBuffer>(count);
}

glm::vec2 GLRenderer::getRenderResolution() const
{
	GLint curViewport[4];
	glGetIntegerv(GL_VIEWPORT, curViewport);
	return glm::vec2(curViewport[2], curViewport[3]);
}
