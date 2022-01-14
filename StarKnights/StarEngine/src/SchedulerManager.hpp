#ifndef SCHEDULER_MANAGER_HPP
#define SCHEDULER_MANAGER_HPP

#include <chrono>
#include <vector>
#include <functional>

using fseconds = std::chrono::duration<float>;
using handler_fun = std::function<void(fseconds)>;

class SchedulerManager {
public:
	explicit SchedulerManager();
	void update();
	std::chrono::duration<float> getCurrentDelta() const;

	struct HandlerStorage
	{
		handler_fun func;

		fseconds delay;
		fseconds delta;
		size_t count;

		size_t tag;

		std::chrono::high_resolution_clock::time_point lastTime;
	};
	void schedulerUpdate(handler_fun fun, size_t tag) const;
	void scheduler(handler_fun func, fseconds delay, fseconds delta, size_t count, size_t key) const;
	void stop(size_t key) const;
private:
	mutable std::vector<std::pair<size_t, handler_fun>> _handlers;
	std::chrono::high_resolution_clock::time_point _prevTime;
	fseconds _delta{};
};

#endif SCHEDULER_MANAGER_HPP