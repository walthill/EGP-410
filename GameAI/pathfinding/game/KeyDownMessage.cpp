#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "GridGraph.h"
#include "KeyDownMessage.h"
#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "Vector2D.h"
#include "component steering/UnitManager.h"
#include "SpriteManager.h"


KeyDownMessage::KeyDownMessage(const int& key)
	:GameMessage(BUTTON_DOWN)
	, mKey(key)
{
}

KeyDownMessage::~KeyDownMessage()
{
}

void KeyDownMessage::initializePlayerPathing(Vector2D pos)
{
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	//clear pool
	gpGameApp->getPathPool()->resetPathUse();
	//clear gpPaths
	int size = gpGameApp->gpPaths.size();
	for (int i = 0; i < size; i++)
	{
		delete gpGameApp->gpPaths[0];
		gpGameApp->gpPaths.erase(gpGameApp->gpPaths.begin());
	}

	gpGame->getUnitManager()->getPlayerUnit()->generatePath(pos);

}

void KeyDownMessage::process()
{
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);

	if (gpGameApp != NULL)
	{
		//exit game
		if (mKey == ESCAPE_KEY)
		{
			gpGame->markForExit();
		}
		else if (mKey == R_KEY)
		{
			if (gpGameApp->getUnitManager()->getPlayerUnit()->stateMachineActive())
			{
				cout << "TOGGLE STATE MACHINE: OFF" << endl;
				gpGameApp->getUnitManager()->getPlayerUnit()->setStateMachine(false);
			}
			else
			{
				cout << "ASSUMING CONTROL OF THIS FORM" << endl;
				gpGameApp->getUnitManager()->getPlayerUnit()->setStateMachine(true);
			}
		}
		else if (mKey == W_KEY && gpGameApp->getInputManager()->currentEvent != W_KEY)
		{
			if (gpGameApp->getUnitManager()->getPlayerUnit()->stateMachineActive())
			{
				cout << "TOGGLE STATE MACHINE: OFF - Returning to player control" << endl;
				gpGameApp->getUnitManager()->getPlayerUnit()->setStateMachine(false);
			}

			gpGameApp->getInputManager()->currentEvent = W_KEY;

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestUp(playerPos.getX(), 0.0f);
			Vector2D posToStopAt;

			clearPathRaycast(playerPos, farthestUp, posToStopAt);

			if (gpGameApp->getGrid()->getSquareIndexFromPixelXY(posToStopAt.getX(), posToStopAt.getY())
				== gpGameApp->getGrid()->getSquareIndexFromPixelXY(playerPos.getX(), playerPos.getY()))
			{
				gpGameApp->getInputManager()->currentEvent = INVALID_KEY;
				return;
			}
			else
				initializePlayerPathing(posToStopAt);
		}
		else if (mKey == A_KEY && gpGameApp->getInputManager()->currentEvent != A_KEY)
		{
			if (gpGameApp->getUnitManager()->getPlayerUnit()->stateMachineActive())
			{
				cout << "TOGGLE STATE MACHINE: OFF - Returning to player control" << endl;
				gpGameApp->getUnitManager()->getPlayerUnit()->setStateMachine(false);
			}

			gpGameApp->getInputManager()->currentEvent = A_KEY;

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestLeft(0.0f, playerPos.getY());
			Vector2D posToStopAt;

			clearPathRaycast(playerPos, farthestLeft, posToStopAt);

			if (gpGameApp->getGrid()->getSquareIndexFromPixelXY(posToStopAt.getX(), posToStopAt.getY())
				== gpGameApp->getGrid()->getSquareIndexFromPixelXY(playerPos.getX(), playerPos.getY()))
			{
				gpGameApp->getInputManager()->currentEvent = INVALID_KEY;
				return;
			}
			else
				initializePlayerPathing(posToStopAt);
		}
		else if (mKey == S_KEY && gpGameApp->getInputManager()->currentEvent != S_KEY)
		{
			if (gpGameApp->getUnitManager()->getPlayerUnit()->stateMachineActive())
			{
				cout << "TOGGLE STATE MACHINE: OFF - Returning to player control" << endl;
				gpGameApp->getUnitManager()->getPlayerUnit()->setStateMachine(false);
			}

			gpGameApp->getInputManager()->currentEvent = S_KEY;

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestDown(playerPos.getX(), 767.0f);
			Vector2D posToStopAt;

			clearPathRaycast(playerPos, farthestDown, posToStopAt);

			if (gpGameApp->getGrid()->getSquareIndexFromPixelXY(posToStopAt.getX(), posToStopAt.getY())
				== gpGameApp->getGrid()->getSquareIndexFromPixelXY(playerPos.getX(), playerPos.getY()))
			{
				gpGameApp->getInputManager()->currentEvent = INVALID_KEY;
				return;
			}
			else
				initializePlayerPathing(posToStopAt);
		}
		else if (mKey == D_KEY && gpGameApp->getInputManager()->currentEvent != D_KEY) //GO RIGHT
		{
			if (gpGameApp->getUnitManager()->getPlayerUnit()->stateMachineActive())
			{
				cout << "TOGGLE STATE MACHINE: OFF - Returning to player control" << endl;
				gpGameApp->getUnitManager()->getPlayerUnit()->setStateMachine(false);
			}

			gpGameApp->getInputManager()->currentEvent = D_KEY;

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestRight(1023.0f, playerPos.getY());
			Vector2D posToStopAt;

			clearPathRaycast(playerPos, farthestRight, posToStopAt);
			
			if (gpGameApp->getGrid()->getSquareIndexFromPixelXY(posToStopAt.getX(), posToStopAt.getY())
				== gpGameApp->getGrid()->getSquareIndexFromPixelXY(playerPos.getX(), playerPos.getY()))
			{
				gpGameApp->getInputManager()->currentEvent = INVALID_KEY;
				return;
			}
			else			
				initializePlayerPathing(posToStopAt);
		}
	}
}


bool KeyDownMessage::clearPathRaycast(Vector2D fromPos, Vector2D toPos, Vector2D& deadEndPos)
{
	const int RAY_ITERATORS = 100;
	GameApp* pGameApp = dynamic_cast<GameApp*>(gpGame);
	float previousX = 0, previousY = 0;
	Vector2D direction;
	bool result = true;

	direction = toPos - fromPos;

	float posX = fromPos.getX();
	float posY = fromPos.getY();

	for (size_t i = 0; i < RAY_ITERATORS; i++)
	{
		bool pathBlocked = pGameApp->getGrid()->getValueAtPixelXY((int)posX, (int)posY) == BLOCKING_VALUE;

		if (pathBlocked)
		{
			result = false;
			break;
		}
		else
		{
			//capture open position just before the wall
			previousX = posX;
			previousY = posY;
			deadEndPos.setX(previousX);
			deadEndPos.setY(previousY);
		}

		//shoot raycast
		posX = posX + (direction.getX() / RAY_ITERATORS);
		posY = posY + (direction.getY() / RAY_ITERATORS);
	}

	return result;
}
