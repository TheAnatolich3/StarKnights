#ifndef USER_MENU_HPP
#define USER_MENU_HPP
#include <MenuItem.hpp>
class Engine;

class UserMenu
{
public:
	explicit UserMenu(const Engine& engine);
	~UserMenu() = default;

	void init();
	void update();

	float getVolume() const;
private:
	const Engine& _engine;

	std::shared_ptr<Menu::Button> _playButton;
	std::shared_ptr<Menu::Button> _settingsButton;
	std::shared_ptr<Menu::Button> _quitButton;
	std::shared_ptr<Menu::Button> _backButton;
	std::shared_ptr<Menu::BeginItem> _beginMainMenu;
	std::shared_ptr<Menu::BeginItem> _beginSettings;
	std::shared_ptr<Menu::EndItem> _end;

	std::shared_ptr<Menu::Slider> _slider;
};

#endif USER_MENU_HPP