#pragma once

#include <SDL\SDL.h>
#include <memory>

class ScreenList;
class GameScreen;

class Game {
public:
	Game();
	virtual ~Game();

	void Run();
	void Exit();

	virtual void OnInit() = 0;
	virtual void AddScreens() = 0;
	virtual void OnExit() = 0;
protected:
	virtual void ProcessInput(float dt);
	virtual void Update(float dt);
	virtual void Draw();

	void InitScreens();

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	GameScreen* m_currentScreen = nullptr;
	std::unique_ptr<ScreenList> m_screenList = nullptr;
};