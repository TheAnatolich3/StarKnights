#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string_view>
#include <EventsManager.hpp>
#include <memory>
#include <glm/glm.hpp>

class Window;
class Node;
class Renderer;
class SchedulerManager;
class b2World;

class Engine : public EventsManager::Delegate {
public:

	explicit Engine();
	~Engine();

	void init(std::string_view name_window, size_t width, size_t height);

	void update();
	bool isActive();

	void handle_event(QuitEvent ev);

	glm::vec2 getVirtualResolution() const;
	void setVirtualResolution(glm::vec2 virtualResolution) const;

	[[nodiscard]] const EventsManager& eventsManager() const;
	[[nodiscard]] const Renderer& renderer() const;
	[[nodiscard]] const Window& window() const;
	[[nodiscard]] const SchedulerManager& schedulerManager() const;
	[[nodiscard]] const b2World& world() const;

	std::shared_ptr<Node> getCamera() const;
	std::shared_ptr<Node> scene();
private:
	bool _isActive = false;

	std::shared_ptr<Node> _scene;
	std::shared_ptr<Node> _camera;
	std::unique_ptr<b2World> _world;
	std::unique_ptr<Window> _window;
	std::unique_ptr<EventsManager> _eventsManager;
	std::unique_ptr<SchedulerManager> _schedulerManager;
	std::unique_ptr<Renderer> _renderer;

	mutable glm::vec2 _virtualResolution;
};

#endif ENGINE_HPP