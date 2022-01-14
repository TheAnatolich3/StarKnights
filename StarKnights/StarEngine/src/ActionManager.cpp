//#include "ActionManager.hpp"
//
//void Action::setTag(size_t t)
//{
//	_tag = t;
//}
//
//size_t Action::getTag() const
//{
//	return _tag;
//}
//
//std::shared_ptr<Action> ActionManager::addAction(std::shared_ptr<Action> action)
//{
//	_actions.push_back(std::move(action));
//}
//
//void ActionManager::removeAction(std::shared_ptr<Action> action)
//{
//	_action.remove(action);
//}
//
//void ActionManager::removeActionByTag(size_t tag)
//{
//	//todo
//}
//
//MoveBy::MoveBy(glm::vec2 offset, fseconds duration):
//	_offset(offset), _duration(duration)
//{
//
//}
//
//void MoveBy::update(float value)
//{
//	Action:update(value);
//	if (_target)
//	{
//		auto delta = glm::mix(glm::vec2(0), _offset, value);
//		auto delta = _target->
//	}
//}