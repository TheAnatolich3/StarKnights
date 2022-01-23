#ifndef AUDIO_MENU_HPP
#define AUDIO_MENU_HPP

#include <vector>
#include <EventsManager.hpp>

class Engine;
class Sound;

class AudioMenu : public EventsManager::Delegate{
public:
	explicit AudioMenu(const Engine&);
	~AudioMenu();

	void play();
	void pause();
	void next();
	void previous();

	void update();

	void set_volume(int);
private:
	const Engine& _engine;

	std::vector<std::shared_ptr<Sound>> _playlist;
};
#endif AUDIO_MENU_HPP