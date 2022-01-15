#pragma once
#ifndef EVENTS_MANAGER_HPP
#define EVENTS_MANAGER_HPP
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <Utils/GeneralUtils.hpp>

enum class Action
{
	Down,
	Up
};

struct KeyEvent
{
	Action type;
	utils::KeyCode key;
};

enum class MouseButton
{
	Left,
	Right,
	Middle
};

struct MouseEvent
{
	glm::vec2 pos;
	Action type;
	MouseButton button;
};

struct MouseMoveEvent
{
	glm::vec2 pos;
};

struct TextInputEvent
{
	std::string string;

	explicit TextInputEvent(std::string string)
		: string(std::move(string))
	{}
};

struct MouseWheelEvent
{
	int value;
	explicit MouseWheelEvent(int value) : value(value) { }
};

struct QuitEvent {};

class EventsManager {
public:
	struct Delegate
	{
		virtual void handle_event(QuitEvent) {};
		virtual void handle_event(KeyEvent) {};
		virtual void handle_event(MouseEvent) {};
		virtual void handle_event(TextInputEvent) {};
		virtual void handle_event(MouseMoveEvent) {};
		virtual void handle_event(MouseWheelEvent) {};
	};

	template<typename T>
	void invoke_event(T event) const
	{
		for (auto delegate : _delegates)
		{
			delegate->handle_event(event);
		}
	}

	void add_delegate(Delegate* delegate) const;
private:
	mutable std::vector<Delegate*> _delegates;
};

#endif EVENTS_MANAGER_HPP