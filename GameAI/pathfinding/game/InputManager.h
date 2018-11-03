#pragma once
#include <Trackable.h>

class GameApp;

class InputManager
{
public:

	InputManager();
	~InputManager();

	void process();

private:
	GameApp* gpGameApp;
	int x, y;
	int iNum;
};

