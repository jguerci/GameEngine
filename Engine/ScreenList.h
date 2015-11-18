/* Credit goes to Ben Arnold of SoA for the screenlist-gamescreen architecture */

#pragma once

#include <vector>

class Game;
class GameScreen;

class ScreenList {
public:
	ScreenList(Game* game);
	~ScreenList();

	GameScreen* MoveNext();
	GameScreen* MovePrevious();

	void SetScreen(int nextScreen);
	void AddScreen(GameScreen* newScreen);

	void Destroy();

	GameScreen* GetCurrent();
protected:
	Game* m_game = nullptr;
	std::vector<GameScreen*> m_screens;
	int m_currentScreenIndex = -1;
};