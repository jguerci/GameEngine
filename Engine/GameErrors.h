#pragma once

#include <string>
#include <iostream>

#include "Window.h"

using namespace std;

static void GameError(const std::string& error)
{
	cout << error << endl << endl;
	system("pause");
	Window::Destroy();
	exit(1);
}