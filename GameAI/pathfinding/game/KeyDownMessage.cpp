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
		else if (mKey == W_KEY && gpGameApp->getInputManager()->currentEvent != W_KEY)
		{
			gpGameApp->getInputManager()->currentEvent = W_KEY;

			PhysicsData data;
			data.vel = 0;
			data.acc = 0;
			gpGameApp->getUnitManager()->getPlayerUnit()->getPhysicsComponent()->setData(data);

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestUp(playerPos.getX(), 0.0f);
			Vector2D posToStopAt;

			bool test = clearPathRaycast(playerPos, farthestUp, posToStopAt);
	
			if (test)
				initializePlayerPathing(farthestUp);
			else
				initializePlayerPathing(posToStopAt);
		}
		else if (mKey == A_KEY && gpGameApp->getInputManager()->currentEvent != A_KEY)
		{
			gpGameApp->getInputManager()->currentEvent = A_KEY;

			PhysicsData data;
			data.vel = 0;
			data.acc = 0;
			gpGameApp->getUnitManager()->getPlayerUnit()->getPhysicsComponent()->setData(data);

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestLeft(0.0f, playerPos.getY());
			Vector2D posToStopAt;

			bool test = clearPathRaycast(playerPos, farthestLeft, posToStopAt);

			if (test)
				initializePlayerPathing(farthestLeft);
			else
				initializePlayerPathing(posToStopAt);
		}
		else if (mKey == S_KEY && gpGameApp->getInputManager()->currentEvent != S_KEY)
		{
			gpGameApp->getInputManager()->currentEvent = S_KEY;


			PhysicsData data;
			data.vel = 0;
			data.acc = 0;
			gpGameApp->getUnitManager()->getPlayerUnit()->getPhysicsComponent()->setData(data);

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestDown(playerPos.getX(), 767.0f);
			Vector2D posToStopAt;

			bool test = clearPathRaycast(playerPos, farthestDown, posToStopAt);

			if (test)
				initializePlayerPathing(farthestDown);
			else
				initializePlayerPathing(posToStopAt);
		}
		else if (mKey == D_KEY && gpGameApp->getInputManager()->currentEvent != D_KEY) //GO RIGHT
		{
			gpGameApp->getInputManager()->currentEvent = D_KEY;

			PhysicsData data;
			data.vel = 0;
			data.acc = 0;
			gpGameApp->getUnitManager()->getPlayerUnit()->getPhysicsComponent()->setData(data);

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestRight(1023.0f, playerPos.getY());
			Vector2D posToStopAt;

			bool test = clearPathRaycast(playerPos, farthestRight, posToStopAt);
			
			if(test)
				initializePlayerPathing(farthestRight);
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
			//if raycast fails on first fire
			if (previousX == 0 && previousY == 0)
			{
				previousX = pGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition().getX();
				previousY = pGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition().getY();
			}

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
