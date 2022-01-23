#include <iostream>
#include <string_view>
#include <Engine.hpp>
#include <Box2d/Box2d.h>
#include <Sprite.hpp>
#include <Window.hpp>
#include <Button.hpp>
#include "Game/Earth.hpp"

int main(int argc, char* argv[])
{
	Engine engine{};
	engine.init("StarKnights", 1280, 720);

	std::shared_ptr<Button> pause_button = std::make_shared<Button>(engine, "../../../../StarKnights/res/pause_80.png");
	std::shared_ptr<Button> play_button = std::make_shared<Button>(engine, "../../../../StarKnights/res/play_80.png");
	std::shared_ptr<Button> prev_button = std::make_shared<Button>(engine, "../../../../StarKnights/res/prev_80.png");
	std::shared_ptr<Button> next_button = std::make_shared<Button>(engine, "../../../../StarKnights/res/next_80.png");
	std::cout << play_button->getAnchor().x << " " << play_button->getAnchor().y << std::endl;
	prev_button->setScale(glm::vec2(0.7f));
	prev_button->setPosition(prev_button->getContentSize() * prev_button->getScale() * glm::vec2(0.5f, 0.5f));
	play_button->setScale(glm::vec2(0.7f));
	play_button->setPosition(play_button->getContentSize() * play_button->getScale() * glm::vec2(1.5f, 0.5f));
	next_button->setScale(glm::vec2(0.7f));
	next_button->setPosition(next_button->getContentSize() * next_button->getScale() * glm::vec2(2.5f, 0.5f));
	pause_button->setScale(glm::vec2(0.7f));
	pause_button->setPosition(pause_button->getContentSize() * pause_button->getScale() * glm::vec2(1.5f, 0.5f));
	engine.scene()->addNode(play_button);
	engine.scene()->addNode(prev_button);
	engine.scene()->addNode(next_button);

	//auto back = std::make_shared<Sprite>(engine, "../../../../StarKnights/res/land.jpg");
	////back->setPosition(glm::vec2(10.0f, 0.0f));
	//back->setScale(glm::vec2(0.1f));
	//back->setAnchor(glm::vec2(0.0f));
	//engine.scene()->addNode(back);

	/*for (int j = 0; j < 8; ++j)
	{
		auto back = std::make_shared<Earth>(engine);
		back->setScale(glm::vec2(0.1f));
		back->setAnchor(glm::vec2(0.5f));
		back->setPosition(back->getContentSize()*back->getScale() * glm::vec2{j, 3.85});
		engine.scene()->addNode(back);
	}*/


		
	while (engine.isActive())
	{
		engine.update();
	}
	return 0;
}
