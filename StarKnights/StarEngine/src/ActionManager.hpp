#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP
#include <memory>
#include <vector>
#include <SchedulerManager.hpp>
#include <glm/glm.hpp>
#include <Node.hpp>
//using namespace chrono_litarals;

class Action
{
public:
	Action() {}
	Action(const fseconds);
	void setTag(size_t);
	size_t getTag() const;

	void step(fseconds dt);
	virtual void update(float value){};
private:
	fseconds _duration;
	//fseconds _elapes = 0s;
	size_t _tag;

	Node* _target;
};


class MoveBy : public Action
{
public:
	MoveBy(glm::vec2 offset, fseconds duration);
	void update(float value) override;
private:
	glm::vec2 _offset;
	fseconds _duration;
};

class ActionManager
{
public:
	std::shared_ptr<Action> addAction(std::shared_ptr<Action> action);
	void removeAction(std::shared_ptr<Action> action);
	void removeActionByTag(size_t tag);

	void update(fseconds );
private:
	std::vector <std::shared_ptr<Action>> _actions;
};
#endif ACTIONMANAGER_HPP