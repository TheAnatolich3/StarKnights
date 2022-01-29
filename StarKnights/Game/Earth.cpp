#include <Engine.hpp>
#include <Sprite.hpp>
#include "Earth.hpp"

Earth::Earth(Engine& engine)
	: Node(engine)
{
	_land = std::make_shared<Sprite>(engine, "land.jpg");
	_contentSize = _land->getContentSize();
	this->addNode(_land);
}

void Earth::update(fseconds dt)
{

}