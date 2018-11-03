#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "KeyDownMessage.h"
#include "GameMessage.h"

#include "InputManager.h"


InputManager::InputManager()
{
	gpGameApp = dynamic_cast<GameApp*>(gpGame);
}

InputManager::~InputManager()
{
}

void InputManager::process()
{
	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	int x, y;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		static Vector2D lastPos(0.0f, 0.0f);
		Vector2D pos(x, y);
		if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
		{
			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			gpGameApp->mpMessageManager->addMessage(pMessage, 0);
			lastPos = pos;
		}
	}

	//get keyboard state
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	//If escape key was down then exit the loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		GameMessage* pMessage = new KeyDownMessage(0);
		gpGameApp->mpMessageManager->addMessage(pMessage, 1);
	}
	// Depth first 
	if (state[SDL_SCANCODE_F])
	{
		GameMessage* pMessage = new KeyDownMessage(1);
		gpGameApp->mpMessageManager->addMessage(pMessage, 1);
	}
	// Dijkstra
	if (state[SDL_SCANCODE_D])
	{
		GameMessage* pMessage = new KeyDownMessage(2);
		gpGameApp->mpMessageManager->addMessage(pMessage, 1);
	}
	// A*
	if (state[SDL_SCANCODE_A])
	{
		GameMessage* pMessage = new KeyDownMessage(3);
		gpGameApp->mpMessageManager->addMessage(pMessage, 1);
	}

}