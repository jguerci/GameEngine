#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

class Window
{
public:
	static void Create(int width, int height, const std::string& title);
	static void Destroy();

	static void ClearBuffers();
	static void SwapBuffers();

	static int GetWidth();
	static int GetHeight();
	static bool IsRunning();
	static SDL_Window* GetSDLWindow();

	static void SetIsRunning(bool value);
	static void SetMousePosition(int x, int y);
private:
	static int width;
	static int height;
	static std::string title;
	static SDL_Window* window;
	static SDL_GLContext glContext;
	static bool isRunning;
};