#include <iostream>
#include <string_view>
#include <Engine.hpp>
#include <Box2d/Box2d.h>
#include <Sprite.hpp>
#include <Window.hpp>
#include "Game/Earth.hpp"

int main(int argc, char* argv[])
{
	//
	Engine engine{};
	engine.init("StarKnights", 1280, 720);

	for (int j = -3; j < 4; ++j)
	{
		auto back = std::make_shared<Earth>(engine);
		back->setScale(glm::vec2(0.1f));
		std::cout << back->getPosition().x << " " << back->getPosition().y << std::endl;
		back->setPosition(back->getContentSize()*back->getScale() * glm::vec2{j, 1.45});
		std::cout << back->getPosition().x << " " << back->getPosition().y << std::endl;
		engine.scene()->addNode(back);
	}
		
	while (engine.isActive())
	{
		engine.update();
	}
	return 0;
}
