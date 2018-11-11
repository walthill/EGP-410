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
					x = mEvent.motion.x;
					y = mEvent.motion.y;
					Vector2D pos(x, y);

					//loop thru all non player units
					for (unsigned int i = 1; i < gpGame->getUnitManager()->size()+1; i++)
						gpGame->getUnitManager()->getUnit(i)->generatePath(pos);
				}
				break;

			case SDL_KEYDOWN:
				if (mEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					GameMessage* pMessage = new KeyDownMessage(0);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
				if (mEvent.key.keysym.sym == SDLK_f)
				{
					GameMessage* pMessage = new KeyDownMessage(1);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
				if (mEvent.key.keysym.sym == SDLK_d)
				{
					GameMessage* pMessage = new KeyDownMessage(2);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
				if (mEvent.key.keysym.sym == SDLK_a)
				{
					GameMessage* pMessage = new KeyDownMessage(3);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
				if (mEvent.key.keysym.sym == SDLK_s)
				{
					GameMessage* pMessage = new KeyDownMessage(4);
					gpGameApp->mpMessageManager->addMessage(pMessage, 1);
				}
			break;
			default:
				break;
		}
	}
}