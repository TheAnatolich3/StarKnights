#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <glm/glm.hpp>
#include <vector>
#include <string_view>
#include <optional>

class Engine;

class Node : public std::enable_shared_from_this<Node>
{
public:
	explicit Node(const Engine& engine);

	virtual ~Node();
	void visit();
	void addNode(std::shared_ptr<Node> node);
	void removeNode(std::shared_ptr<Node> node);
	void removeFromParent();

	Node* getParent();

	const glm::vec2& getPosition() const;
	void setPosition(const glm::vec2& position);

	const glm::vec2& getScale() const;
	void setScale(const glm::vec2& scale);

	const glm::float32 getRotation() const;
	void setRotation(float rotation);

	const glm::vec2& getAnchor() const;
	void setAnchor(const glm::vec2& anchor);

	const glm::vec2& getContentSize() const;
	void setContentSize(const glm::vec2& contentSize);

	glm::mat3 getTransform();
	std::vector<std::shared_ptr<Node>> getChilds();

	int getOrder() const;
	void setOrder(int value);
protected:
	virtual void visitSelf() {};

	const Engine& _engine;
	Node* _parent = nullptr;
	size_t _id;
	mutable std::vector<std::shared_ptr<Node>> _nodes;

	glm::vec2 _position = glm::vec2(0.0f);
	glm::vec2 _scale = glm::vec2(1.0f);
	glm::vec2 _anchor = glm::vec2(0.5f);
	glm::float32 _rotation = 0.0f;
	glm::vec2 _contentSize = glm::vec2(0.0f);
	std::optional<glm::mat3> _transform;
	int _zOrder = 0;
};

#endif NODE_HPP