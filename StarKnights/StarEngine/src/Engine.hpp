#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string_view>
#include <EventsManager.hpp>
#include <memory>

class Window;
class Renderer;

class Engine : public EventsManager::Delegate {
public:

	explicit Engine();
	~Engine();

	void init(std::string_view name_window, size_t width, size_t height);

	void update();
	bool isActive();

	void handle_event(QuitEvent ev);

	[[nodiscard]] const EventsManager& eventsManager() const;
	[[nodiscard]] const Renderer& renderer() const;
	[[nodiscard]] const Window& window() const;

private:
	bool _isActive = false;

	std::unique_ptr<Window> _window;
	std::unique_ptr<EventsManager> _eventsManager;
	std::unique_ptr<Renderer> _renderer;
};

#endif ENGINE_HPP