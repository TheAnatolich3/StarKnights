#include <Engine.hpp>
#include <Sprite.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include "Button.hpp"


Button::Button(const Engine& engine, std::string_view file_name)
	: Node(engine)
{
	_body = std::make_shared<Sprite>(engine, file_name.data());
	_body->setPosition(_body->getContentSize() * 0.5f);
	this->setContentSize(_body->getContentSize());
	this->addNode(_body);
	engine.eventsManager().add_delegate(this);
}

void Button::visitSelf()
{

}


void Button::handle_event(MouseEvent me)
{
	glm::vec2 button_size = this->getContentSize() * this->getScale();
	glm::vec2 button_pos = this->getPosition();
	if (me.pos.x > button_pos.x - button_size.x / 2
		&& me.pos.x < button_pos.x + button_size.x / 2
		&& me.pos.y > button_pos.y - button_size.y / 2
		&& me.pos.y < button_pos.y + button_size.y / 2
		&& me.type == Action::Down
		&& me.button == MouseButton::Left)
	{
		this->setScale(glm::vec2(0.65f));
		_status = false;
	}
	else
	{
		this->setScale(glm::vec2(0.7f));
	}
}

bool Button::getStatus() const
{
	return _status;
}

void Button::setHandleStatus()
{
	_status = true;
}