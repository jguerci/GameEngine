#pragma once

#include <glm\glm.hpp>

using namespace glm;

class Input
{
public:
	static void Update();

	static bool KeyHeld(unsigned int keyID);
	static bool KeyPressed(unsigned int keyID);
	static vec2 MousePosition();

	static void SetCursor(bool value);
	static void SetMousePosition(vec2 pos);
protected:
private:
};
