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
	/*				//clear pool
					gpGameApp->getPathPool()->resetPathUse();
					//clear gpPaths
					int size = gpGameApp->gpPaths.size();
					for (int i = 0; i < size; i++)
					{
						delete gpGameApp->gpPaths[0];
						gpGameApp->gpPaths.erase(gpGameApp->gpPaths.begin());
					}

					x = mEvent.motion.x;
					y = mEvent.motion.y;
					Vector2D pos(0, 768 * 0.5); // middle left

					cout << "player Pathfinding" << endl;
					//pathfind for player player units
					gpGame->getUnitManager()->getPlayerUnit()->generatePath(pos);
*/				}
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