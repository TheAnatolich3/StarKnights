#pragma once
#ifndef GAME_SDLWINDOW_HPP
#define GAME_SDLWINDOW_HPP

#include <Window.hpp>
#include <string_view>

class Engine;
class SDL_Window;

class SDLWindow final : public Window
{
public:
	SDLWindow(const Engine& engine,
		std::string_view name,
		size_t width,
		size_t height);

	void update() override;
	void swap() override;

	std::unique_ptr<Renderer> createRenderer() override;

	std::string_view getClipboardText() const override;
	void setClipboardText(std::string_view text) const override;

private:
	std::shared_ptr<SDL_Window> _window;
	const Engine& _engine;

	mutable std::string _clipboard;
};

#endif GAME_SDLWINDOW_HPP