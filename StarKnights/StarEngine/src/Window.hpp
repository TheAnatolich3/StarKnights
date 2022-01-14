#pragma once
#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <memory>
#include <string_view>
#include <glm/glm.hpp>

class Renderer;

class Window
{
public:
	virtual ~Window() = default;

	Window(size_t width, size_t height) :
		_width(width), _height(height)
	{}

	size_t getWidth() const
	{
		return _width;
	}

	size_t getHeight() const
	{
		return _height;
	}

	virtual void update() = 0;
	virtual void swap() = 0;

	virtual std::unique_ptr<Renderer> createRenderer() = 0;

	glm::vec2 getScaleFactor() const
	{
		return _scaleFactor;
	}

	virtual std::string_view getClipboardText() const = 0;
	virtual void setClipboardText(std::string_view text) const = 0;
protected:
	size_t _width;
	size_t _height;

	glm::vec2 _scaleFactor = { 1.0f, 1.0f };
};

#endif GAME_WINDOW_HPP
