#pragma once
#include <Trackable.h>

class GameApp;

enum KeyEvents
{
	INVALID_KEY = -1,
	W_KEY, A_KEY, S_KEY, D_KEY, ESCAPE_KEY
};

class InputManager
{
public:

	KeyEvents currentEvent = INVALID_KEY;
	InputManager();
	~InputManager();

	void process();

private:
	GameApp* gpGameApp;
	int x, y;
	int iNum;
	SDL_Event mEvent;
};