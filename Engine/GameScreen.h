#pragma once

#define SCREEN_INDEX_NO_SCREEN -1

class Game;

enum class ScreenState {
	NONE,
	RUNNING,
	EXIT_APPLICATION,
	CHANGE_NEXT,
	CHANGE_PREVIOUS
};

class GameScreen {
public:
	friend class ScreenList;

	GameScreen() {}
	virtual ~GameScreen() {}

	// Return the index of the next or previous screen when changing screens
	virtual int GetNextScreenIndex() const = 0;
	virtual int GetPreviousScreenIndex() const = 0;

	// Called at beginning and end of application
	virtual void Build() = 0;
	virtual void Destroy() = 0;

	// Called when a screen enters and exits focus
	virtual void OnEntry() = 0;
	virtual void OnExit() = 0;

	// Called in the main game loop
	virtual void ProcessInput(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

	// Gets the index of the current screen
	int GetScreenIndex() const {
		return m_screenIndex;
	}
	void SetRunning() {
		m_currentState = ScreenState::RUNNING;
	}

	ScreenState GetState() const { return m_currentState; }

	/// Sets m_game to the parent game
	void SetParentGame(Game* game) { m_game = game; }

protected:
	ScreenState m_currentState = ScreenState::NONE;
	Game* m_game = nullptr;
	int m_screenIndex = -1;
};