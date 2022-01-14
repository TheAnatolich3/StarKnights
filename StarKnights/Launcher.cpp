// StarKnights.cpp: определяет точку входа для приложения.
//
#include <iostream>
#include <string_view>
#include <Engine.hpp>

int main(int argc, char* argv[])
{
	Engine engine{};
	engine.init("StarKnights", 1280, 720);
	while (engine.isActive())
	{
		engine.update();
	}
	return 0;
}
