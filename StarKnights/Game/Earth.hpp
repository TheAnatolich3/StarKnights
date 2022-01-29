#ifndef EARTH_HPP
#define EARTH_HPP

#include <Node.hpp>

class Earth : public Node
{
public:
	explicit Earth(Engine&);

	void update(fseconds dt) override;
private:
	std::shared_ptr<Node> _land; 
};

#endif EARTH_HPP