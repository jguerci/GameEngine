#include "input.h"
#include "Window.h"
#include <SDL\SDL.h>
#include <unordered_map>

static SDL_Event e;

static glm::vec2 mouseCoords;
std::unordered_map<unsigned int, bool> keys;
std::unordered_map<unsigned int, bool> previousKeys;

void Input::Update()
{
	for (auto& it : keys) 
	{
		previousKeys[it.first] = it.second;
	}

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				Window::SetIsRunning(false);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				mouseCoords = glm::vec2(e.motion.x, e.motion.y);
				break;
			}
			case SDL_KEYDOWN:
			{
				unsigned int value = e.key.keysym.sym;
				keys[value] = true;
				break;
			}
			case SDL_KEYUP:
			{
				unsigned int value = e.key.keysym.sym;
				keys[value] = false;
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				unsigned int value = e.button.button;
				keys[value] = true;
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				unsigned int value = e.button.button;
				keys[value] = false;
				break;
			}
		}
	}
}

bool Input::KeyHeld(unsigned int keyCode)
{
	return keys[keyCode];
}

bool Input::KeyPressed(unsigned int keyCode)
{
	if (keys[keyCode] && !previousKeys[keyCode]) 
	{
		return true;
	}
	return false;
}

vec2 Input::MousePosition()
{
	return mouseCoords;
}

void Input::SetCursor(bool visible)
{
	if (visible) 
	{
		SDL_ShowCursor(1);
	}
	else
	{
		SDL_ShowCursor(0);
	}
}

void Input::SetMousePosition(vec2 pos)
{
	SDL_WarpMouseInWindow(Window::GetSDLWindow(), (int)pos.x, (int)pos.y);
}