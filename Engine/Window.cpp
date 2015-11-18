#include "Window.h"

#include "GameErrors.h"

int Window::width = 0;
int Window::height = 0;
std::string Window::title = "Title";
SDL_Window* Window::window = nullptr;
SDL_GLContext Window::glContext;
bool Window::isRunning = true;

void Window::Create(int width, int height, const std::string& title)
{
	Window::width = width;
	Window::height = height;
	Window::title = title;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) 
	{
		GameError("Glew failed to init!");
	}
}

void Window::Destroy()
{
	if (!window)
	{
		return;
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::ClearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}

bool Window::IsRunning()
{
	return isRunning;
}

SDL_Window* Window::GetSDLWindow()
{
	return window;
}

void Window::SetIsRunning(bool value)
{
	isRunning = value;
}

void Window::SetMousePosition(int x, int y)
{
	SDL_WarpMouseInWindow(window, x, y);
}