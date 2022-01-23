#include <algorithm>
#include <SDL/SDLWindow.hpp>
#include <Renderer.hpp>
#include <memory>
#include <Node.hpp>
#include <SchedulerManager.hpp>
#include <box2d/box2d.h>
#include <AudioManager.hpp>
#include <UIManager.hpp>
#include "Engine.hpp"

Engine::Engine()
{
	_world = std::make_unique<b2World>(b2Vec2(0.0f, -10.0f));
	_schedulerManager = std::make_unique<SchedulerManager>();
}

Engine::~Engine() = default;

bool Engine::isActive() {
	return _isActive;
}

void Engine::init(std::string_view name_window, size_t width, size_t height)
{
	_isActive = true;
	_virtualResolution = glm::vec2(width, height);
	_scene = std::make_shared<Node>(*this);

	_window = std::make_unique<SDLWindow>(*this, name_window.data(), width, height);
	_renderer = _window->createRenderer();
	_eventsManager = std::make_unique<EventsManager>();
	_audioManager = std::make_unique<AudioManager>();
	_UIManager = std::make_unique<UIManager>(*this);
	_eventsManager->add_delegate(_UIManager.get());
	_eventsManager->add_delegate(this);
	_renderer->init();
}

void Engine::update() {
	_window->update();
	_scene->visit();
	_UIManager->visit();
	_renderer->draw();
	_window->swap();
	_audioManager->update();
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
}


const SchedulerManager& Engine::schedulerManager() const
{
	return *_schedulerManager;
}

std::shared_ptr<Node> Engine::scene()
{
	return _scene;
}

b2World& Engine::world() const
{
	return *_world;
}

const AudioManager& Engine::audioManager() const
{
	return *_audioManager;
}

std::shared_ptr<UIManager> Engine::UI_Manager() const
{
	return _UIManager;
}