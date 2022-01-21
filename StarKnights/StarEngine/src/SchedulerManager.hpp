#ifndef SCHEDULER_MANAGER_HPP
#define SCHEDULER_MANAGER_HPP

#include <chrono>
#include <vector>
#include <functional>

using fseconds = std::chrono::duration<float>;
using namespace std::chrono_literals;

class SchedulerManager {
public:
	explicit SchedulerManager();
	void update();
	fseconds getCurrentDelta() const;

	using handler_fun = std::function<void(fseconds)>;

	void scheduleUpdate(handler_fun fun, size_t tag) const;
	void schedule(handler_fun fun, fseconds delay = 0s, fseconds delta = 0s, size_t count = 0, size_t tag = 0) const;
	void stop(size_t tag) const;

	struct HandlerStorage
	{
		handler_fun fun;

		fseconds delay;
		fseconds delta;
		size_t count;

		size_t tag;
		size_t internalTag;

		std::chrono::high_resolution_clock::time_point lastTime;
	};
private:
	mutable std::vector<HandlerStorage> _handlers;
	std::chrono::high_resolution_clock::time_point _prevTime;
	fseconds _delta{};
	bool _isFirstRun = true;
};

#endif SCHEDULER_MANAGER_HPP