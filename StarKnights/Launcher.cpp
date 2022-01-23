﻿#include <iostream>
#include <string_view>
#include <Engine.hpp>
#include <Box2d/Box2d.h>
#include <Sprite.hpp>
#include <Window.hpp>
#include <Button.hpp>
#include "Game/AudioMenu.hpp"
#include "Game/Earth.hpp"

int main(int argc, char* argv[])
{
	Engine engine{};
	engine.init("StarKnights", 1280, 720);

	std::shared_ptr<AudioMenu> audio_menu = std::make_shared<AudioMenu>(engine);
	engine.scene()->addNode(audio_menu);
	audio_menu->init();
	audio_menu->play();

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
		audio_menu->update();
	}
	return 0;
}
