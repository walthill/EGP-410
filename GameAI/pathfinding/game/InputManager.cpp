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

					for (size_t i = 1; i < gpGame->getUnitManager()->size()+1; i++)
					{
						Vector2D lastPos(gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition().getX(), gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition().getY());
						Vector2D pos(x, y);
						if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
						{
							GameMessage* pMessage = new PathToMessage(lastPos, pos);
							gpGameApp->mpMessageManager->addMessage(pMessage, 0);
							//lastPos = pos;
						}
					}
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