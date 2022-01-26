#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <string_view>
#include <vector>
#include <memory>
#include <mutex>
#include <Sound.hpp>

class Engine;

class AudioManager
{
public:
	AudioManager(const Engine& engine);
	std::shared_ptr<Sound> createSound(std::string_view file_name, bool is_loop, float volume) const;
	void update();

private:
	const Engine& _engine;
	static void audio_callback(void* userdata, uint8_t* stream, int len);
	SDL_AudioDeviceID _audio_device;
	bool pause_status = true;
	SDL_AudioSpec _wanted_spec{};
	mutable std::vector<std::weak_ptr<Sound>> _buffers;
	std::mutex _lock_buffer;
};
#endif AUDIO_MANAGER_HPP