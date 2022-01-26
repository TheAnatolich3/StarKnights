#include <Engine.hpp>
#include <Sprite.hpp>
#include <box2d/box2d.h>
#include "Earth.hpp"

Earth::Earth(Engine& engine)
	: Node(engine)
{
	_land = std::make_shared<Sprite>(engine, "land.jpg");
	_contentSize = _land->getContentSize();
	b2BodyDef groundDef;
	groundDef.position.Set(0.0f, -10.0f);
	_ground = engine.world().CreateBody(&groundDef);

	b2PolygonShape groundShape; 
	groundShape.SetAsBox(100.0f / 2, 20.0f / 2);  
	_ground->CreateFixture(&groundShape, 1.0f);
	this->addNode(_land);
}

void Earth::update(fseconds dt)
{

}