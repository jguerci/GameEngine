#include "Game.h"

#include "ScreenList.h"
#include "GameScreen.h"
#include "Input.h"
#include "Window.h"

#include <iostream>

Game::Game() 
{
	m_screenList = std::make_unique<ScreenList>(this);
}

Game::~Game() 
{
}

void Game::Run() 
{
	InitScreens();

	while (Window::IsRunning()) {
		float currentFrame = SDL_GetTicks();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput(deltaTime);
		Update(deltaTime);
		Draw();
	}
}

void Game::Exit()
{
	m_currentScreen->OnExit();
	if (m_screenList) {
		m_screenList->Destroy();
		m_screenList.reset();
	}
	Window::Destroy();
}

void Game::InitScreens()
{
	OnInit();
	AddScreens();

	m_currentScreen = m_screenList->GetCurrent();
	m_currentScreen->OnEntry();
	m_currentScreen->SetRunning();
}

void Game::ProcessInput(float dt)
{
	Input::Update();

	if (!Window::IsRunning()) {
		Exit();
	}

	if (m_currentScreen) {
		m_currentScreen->ProcessInput(dt);
	}
}

void Game::Update(float dt) 
{
	if (m_currentScreen) {
		switch (m_currentScreen->GetState()) {
			case ScreenState::RUNNING:
				m_currentScreen->Update(dt);
				break;
			case ScreenState::CHANGE_NEXT:
				m_currentScreen->OnExit();
				m_currentScreen = m_screenList->MoveNext();
				if (m_currentScreen) {
					m_currentScreen->SetRunning();
					m_currentScreen->OnEntry();
				}
				break;
			case ScreenState::CHANGE_PREVIOUS:
				m_currentScreen->OnExit();
				m_currentScreen = m_screenList->MovePrevious();
				if (m_currentScreen) {
					m_currentScreen->SetRunning();
					m_currentScreen->OnEntry();
				}
				break;
			case ScreenState::EXIT_APPLICATION:
				Exit();
				break;
			default:
				break;
		}
	}
	else {
		Exit();
	}
}

void Game::Draw() 
{
	glViewport(0, 0, Window::GetWidth(), Window::GetHeight());
	if (m_currentScreen && m_currentScreen->GetState() == ScreenState::RUNNING) {
		m_currentScreen->Draw();
	}
	Window::SwapBuffers();
}