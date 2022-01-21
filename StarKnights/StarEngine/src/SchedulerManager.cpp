#include <Utils/GeneralUtils.hpp>
#include "SchedulerManager.hpp"

SchedulerManager::SchedulerManager()
{
    _prevTime = std::chrono::high_resolution_clock::now();
}

void SchedulerManager::update()
{
    if (_isFirstRun)
    {
        _prevTime = std::chrono::high_resolution_clock::now();
        _isFirstRun = false;
    }

    auto now = std::chrono::high_resolution_clock::now();
    _delta = now - _prevTime;
    _prevTime = now;

    for (auto& handler : _handlers)
    {
        bool needRun = true;
        if (handler.delay.count() > 0.0f)
        {
            auto delta = now - handler.lastTime;
            if (delta >= handler.delay)
            {
                handler.delay = 0s;
            }
            else
            {
                needRun = false;
            }
        }

        if (handler.delta.count() > 0 && (now - handler.lastTime) < handler.delta)
        {
            needRun = false;
        }

        if (needRun)
        {
            handler.lastTime = now;
            handler.fun(_delta);
        }

        if (handler.count != 0)
        {
            --handler.count;

            if (handler.count == 0)
            {
                _handlers.erase(std::remove_if(_handlers.begin(), _handlers.end(), [&](const HandlerStorage& curHandler)
                {
                    return curHandler.internalTag == handler.internalTag;
                }));
            }
        }
    }
}


void SchedulerManager::scheduleUpdate(handler_fun fun, size_t tag) const
{
    this->schedule(std::move(fun), 0s, 0s, 0, tag);
}

void SchedulerManager::schedule(handler_fun func, fseconds delay, fseconds delta, size_t count, size_t key) const
{
    HandlerStorage handler;
    handler.fun = std::move(func);
    handler.count = count;
    handler.delay = delay;
    handler.delta = delta;
    handler.tag = key;
    handler.internalTag = utils::genUniqueObjectId();

    handler.lastTime = std::chrono::high_resolution_clock::now();

    _handlers.push_back(std::move(handler));
}


void SchedulerManager::stop(size_t tag) const
{
    _handlers.erase(std::remove_if(_handlers.begin(), _handlers.end(), [&](const HandlerStorage& curHandler)
    {
        return curHandler.internalTag == tag;
    }));
}

fseconds SchedulerManager::getCurrentDelta() const
{
    return _delta;
}
