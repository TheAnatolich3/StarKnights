#include <Engine.hpp>
#include <Sound.hpp>
#include <Button.hpp>
#include <AudioManager.hpp>
#include "UserMenu.hpp"
#include "AudioMenu.hpp"

AudioMenu::AudioMenu(const Engine& engine, const UserMenu& menu)
	: _engine(engine), _menu(menu), Node(engine)
{
	_pause_button = std::make_shared<Button>(engine, "pause_80.png");
	_play_button = std::make_shared<Button>(engine, "play_80.png");
	_prev_button = std::make_shared<Button>(engine, "prev_80.png");
	_next_button = std::make_shared<Button>(engine, "next_80.png");
	_prev_button->setScale(glm::vec2(0.7f));
	_prev_button->setPosition(_prev_button->getContentSize() * _prev_button->getScale() * glm::vec2(0.5f, 0.5f));
	_play_button->setScale(glm::vec2(0.7f));
	_play_button->setPosition(_play_button->getContentSize() * _play_button->getScale() * glm::vec2(1.5f, 0.5f));
	_next_button->setScale(glm::vec2(0.7f));
	_next_button->setPosition(_next_button->getContentSize() * _next_button->getScale() * glm::vec2(2.5f, 0.5f));
	_pause_button->setScale(glm::vec2(0.7f));
	_pause_button->setPosition(_pause_button->getContentSize() * _pause_button->getScale() * glm::vec2(1.5f, 0.5f));
	this->addNode(_pause_button);
	this->addNode(_prev_button);
	this->addNode(_next_button);
}


void AudioMenu::add_song(std::string_view filepath)
{
	auto song = _engine.audioManager().createSound(filepath, false, 0.8f);
	if (_playlist.empty())
	{
		_current_song = song;
	}
	_playlist.push_back(song);
}

void AudioMenu::play()
{
	_current_song.get()->play();
}

void AudioMenu::pause()
{
	_current_song.get()->pause();
}

void AudioMenu::previous()
{
	_current_song.get()->stop();
	auto it = std::find(_playlist.begin(), _playlist.end(), _current_song);
	if (it == _playlist.begin())
	{
		_current_song = _playlist.back();
	}
	else
	{
		_current_song = *(it - 1);
	}
	_current_song.get()->play();
}

void AudioMenu::next()
{
	_current_song.get()->stop();
	auto it = std::find(_playlist.begin(), _playlist.end(), _current_song);
	if (*it == _playlist.back())
	{
		_current_song = *_playlist.begin();
	}
	else
	{
		_current_song = *(it + 1);
	}
	_current_song.get()->play();
}

void AudioMenu::update()
{
	if (!_next_button->getStatus())
	{
		if (!_current_song->is_playing())
		{
			this->addNode(_pause_button);
			this->removeNode(_play_button);
		}
		next();
		_next_button->setHandleStatus();
	}

	if (!_prev_button->getStatus())
	{
		if (!_current_song->is_playing())
		{
			this->addNode(_pause_button);
			this->removeNode(_play_button);
		}
		previous();
		_prev_button->setHandleStatus();
	}

	if (!_pause_button->getStatus() && _current_song->is_playing())
	{
		_current_song->pause();
		this->addNode(_play_button);
		this->removeNode(_pause_button);
		_pause_button->setHandleStatus();
		_play_button->setHandleStatus();
	}

	if (!_play_button->getStatus() && !_current_song->is_playing())
	{
		_current_song->play();
		this->addNode(_pause_button);
		this->removeNode(_play_button);
		_play_button->setHandleStatus();
		_pause_button->setHandleStatus();
	}

	setVolume(_menu.getVolume());
}

void AudioMenu::setVolume(float volume)
{
	for (auto& song : _playlist)
	{
		song.get()->set_volume(volume);
	}
}

void AudioMenu::init()
{
	add_song("Enemy.wav");
	add_song("One.wav");
	add_song("Trouble.wav");
	add_song("Beautiful.wav");
}