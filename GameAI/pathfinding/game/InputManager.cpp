#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "KeyDownMessage.h"
#include "../game/component steering/UnitManager.h"
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
	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				if (mEvent.button.button == SDL_BUTTON_LEFT)
				{	
				}
				break;

			case SDL_KEYDOWN:
				if (mEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					GameMessage* pMessage = new KeyDownMessage(ESCAPE_KEY);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
				if (mEvent.key.keysym.sym == SDLK_w)
				{
					
					GameMessage* pMessage = new KeyDownMessage(W_KEY);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
				if (mEvent.key.keysym.sym == SDLK_a)
				{
					
					GameMessage* pMessage = new KeyDownMessage(A_KEY);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
				if (mEvent.key.keysym.sym == SDLK_s)
				{
					
					GameMessage* pMessage = new KeyDownMessage(S_KEY);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
				if (mEvent.key.keysym.sym == SDLK_d)
				{
					GameMessage* pMessage = new KeyDownMessage(D_KEY);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
			break;
			default:
				break;
		}
	}
}