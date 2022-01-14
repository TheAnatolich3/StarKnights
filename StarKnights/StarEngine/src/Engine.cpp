#include <algorithm>
#include <SDL/SDLWindow.hpp>
#include <Renderer.hpp>
#include <memory>
#include <Node.hpp>
#include "Engine.hpp"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::isActive() {
	return _isActive;
}

void Engine::init(std::string_view name_window, size_t width, size_t height)
{
	_isActive = true;
	_virtualResolution = glm::vec2(width, height);
	_camera = std::make_shared<Node>(*this);
	_camera->setContentSize(_virtualResolution);

	_window = std::make_unique<SDLWindow>(*this, name_window.data(), width, height);
	_renderer = _window->createRenderer();
	_eventsManager = std::make_unique<EventsManager>();
	_eventsManager->add_delegate(this);
}

void Engine::update() {
	_window->update();
	_renderer->draw();
	_window->swap();
}


const EventsManager& Engine::eventsManager() const
{
	return *_eventsManager;
}

const Renderer& Engine::renderer() const
{
	return *_renderer;
}

const Window& Engine::window() const
{
	return *_window;
}

void Engine::handle_event(QuitEvent ev)
{
	_isActive = false;
}

glm::vec2 Engine::getVirtualResolution() const
{
	return _virtualResolution;
}

void Engine::setVirtualResolution(glm::vec2 virtualResolution) const
{
	_virtualResolution = virtualResolution;
	_camera->setContentSize(_virtualResolution);
}

std::shared_ptr<Node> Engine::getCamera() const
{
	return _camera;
}