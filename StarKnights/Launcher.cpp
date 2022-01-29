#include <iostream>
#include <string_view>
#include <Engine.hpp>
#include <Sprite.hpp>
#include <Window.hpp>
#include <Button.hpp>
#include <UIManager.hpp>
#include <FileManager.hpp>
#include "Game/UserMenu.hpp"
#include "Game/AudioMenu.hpp"
#include "Game/Earth.hpp"

int main(int argc, char* argv[])
{	
	Engine engine{};
	engine.fileManager().setFindPaths({ "StarKnights/res/music/", "StarKnights/res/", "StarKnights/StarEngine/src/Shaders/"});
	engine.init("StarKnights", 1280, 720);
	std::shared_ptr<UserMenu> user_menu = std::make_shared<UserMenu>(engine);
	user_menu->init();

	std::shared_ptr<AudioMenu> audio_menu = std::make_shared<AudioMenu>(engine, *user_menu.get());
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
		user_menu->update();
	}
	return 0;
}
