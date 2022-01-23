#include <Engine.hpp>
#include <UIManager.hpp>
#include "UserMenu.hpp"

UserMenu::UserMenu(const Engine& engine)
	: _engine(engine)
{}

void UserMenu::init()
{
	_beginMainMenu = std::make_shared<Menu::BeginItem>("Main menu");
	_beginSettings = std::make_shared<Menu::BeginItem>("Settings");
	_playButton = std::make_shared<Menu::Button>("Play");
	_settingsButton = std::make_shared<Menu::Button>("Settings");
	_slider = std::make_shared<Menu::Slider>("Volume", 0.0f, 100.0f, 50.0f);
	_backButton = std::make_shared<Menu::Button>("<-- Back");
	_quitButton = std::make_shared<Menu::Button>("Exit");
	_end = std::make_shared<Menu::EndItem>();
	
	_engine.UI_Manager()->addMenuItem(_beginMainMenu);
	_engine.UI_Manager()->addMenuItem(_playButton);
	_engine.UI_Manager()->addMenuItem(_settingsButton);	
	_engine.UI_Manager()->addMenuItem(_quitButton);
	_engine.UI_Manager()->addMenuItem(_end);
}

void UserMenu::update()
{
	if (!_quitButton->getStatus())
	{
		_engine.eventsManager().invoke_event(QuitEvent{});
		_quitButton->setHandleStatus();
	}

	if (!_playButton->getStatus())
	{
		_engine.eventsManager().invoke_event(KeyEvent{ Action::Up, utils::KeyCode::ESCAPE });
		_playButton->setHandleStatus();
	}

	if (!_settingsButton->getStatus())
	{
		_engine.UI_Manager()->removeMenuItem(_beginMainMenu);
		_engine.UI_Manager()->removeMenuItem(_playButton);
		_engine.UI_Manager()->removeMenuItem(_settingsButton);
		_engine.UI_Manager()->removeMenuItem(_quitButton);
		_engine.UI_Manager()->removeMenuItem(_end);

		_engine.UI_Manager()->addMenuItem(_beginSettings);
		_engine.UI_Manager()->addMenuItem(_slider);
		_engine.UI_Manager()->addMenuItem(_backButton);
		_engine.UI_Manager()->addMenuItem(_end);

		_settingsButton->setHandleStatus();
	}

	if (!_backButton->getStatus())
	{
		_engine.UI_Manager()->removeMenuItem(_beginSettings);
		_engine.UI_Manager()->removeMenuItem(_backButton);
		_engine.UI_Manager()->removeMenuItem(_slider);
		_engine.UI_Manager()->removeMenuItem(_end);

		_engine.UI_Manager()->addMenuItem(_beginMainMenu);
		_engine.UI_Manager()->addMenuItem(_playButton);
		_engine.UI_Manager()->addMenuItem(_settingsButton);
		_engine.UI_Manager()->addMenuItem(_quitButton);
		_engine.UI_Manager()->addMenuItem(_end);

		_backButton->setHandleStatus();
	}
}

float UserMenu::getVolume() const
{
	return _slider->getSliderValue();
}