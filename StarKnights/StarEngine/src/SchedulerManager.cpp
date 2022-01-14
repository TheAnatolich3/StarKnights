////#include "SchedulerManager.hpp"
//
//SchedulerManager::SchedulerManager()
//{
//    _prevTime = std::chrono::high_resolution_clock::now();
//}
//
//void SchedulerManager::update()
//{
//    auto now = std::chrono::high_resolution_clock::now();
//    _delta = now - _prevTime;
//    _prevTime = now;
//
//    for (const auto& [key, handler] : _handlers)
//    {
//        handler(_delta);
//    }
//}
//
//
//void SchedulerManager::schedulerUpdate(handler_fun fun, size_t tag) const
//{
//    _handlers.add({ tag, std::move(handler) });
//}
//
//void SchedulerManager::scheduler(handler_fun func, fseconds delay, fseconds delta, size_t count, size_t key) const
//{
//    HandlerStorage handler;
//    handler.func = std::move(func);
//    handler.delay = delay;
//    handler.delta = delta;
//    handler.count = count;
//    handler.tag = key;
//    handler.lastTime = std::chrono::high_resolution_clock::now();
//}
//
//
//void SchedulerManager::stop(size_t tag) const
//{
//    _handlers.removeIf([&](const auto& handlerPair)
//        {
//            const auto& [handlerTag, _] = handlerPair;
//            return handlerTag == tag;
//        });
//}
//
//fseconds SchedulerManager::getCurrentDelta() const
//{
//    return _delta;
//}
