#ifndef AUDIO_MENU_HPP
#define AUDIO_MENU_HPP

#include <vector>
#include <Node.hpp>
#include <EventsManager.hpp>

class Engine;
class Sound;
class Button;

class AudioMenu : public Node, public EventsManager::Delegate{
public:
	explicit AudioMenu(const Engine&);
	~AudioMenu() = default;
	void init();
	void add_song(std::string_view filepath);

	void play();
	void pause();
	void next();
	void previous();

	void update();

	void setVolume(float);
private:
	const Engine& _engine;
	std::vector<std::shared_ptr<Sound>> _playlist;
	std::shared_ptr<Sound> _current_song;

	std::shared_ptr<Button> _pause_button;
	std::shared_ptr<Button> _play_button;
	std::shared_ptr<Button> _prev_button;
	std::shared_ptr<Button> _next_button;
	
};
#endif AUDIO_MENU_HPP