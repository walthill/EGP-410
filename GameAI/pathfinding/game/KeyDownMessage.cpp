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

	//x = mEvent.motion.x;
	//y = mEvent.motion.y;
//	Vector2D pos(0, 768 * 0.5); // middle left

	cout << "player Pathfinding" << endl;
	//pathfind for player player units
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
		else if (mKey == W_KEY)
		{
			PhysicsData data;
			data.vel = 0;
			data.acc = 0;
			gpGameApp->getUnitManager()->getPlayerUnit()->getPhysicsComponent()->setData(data);

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestUp(playerPos.getX(), 0.0f);

			bool test = clearPathRaycast(playerPos, farthestUp);

			cout << test << endl;
			//TODO: raycast for position data to send to pathfinder 

			//768 is max screen height, width - 1024
			//toY - raycast right until blocking path if none, then path to screen bounds
			if (test)
				initializePlayerPathing(farthestUp);
		}
		else if (mKey == A_KEY)
		{
			PhysicsData data;
			data.vel = 0;
			data.acc = 0;
			gpGameApp->getUnitManager()->getPlayerUnit()->getPhysicsComponent()->setData(data);

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestLeft(0.0f, playerPos.getY());

			bool test = clearPathRaycast(playerPos, farthestLeft);

			cout << test << endl;
			//TODO: raycast for position data to send to pathfinder 

			//768 is max screen height, width - 1024
			//toY - raycast right until blocking path if none, then path to screen bounds
			if (test)
				initializePlayerPathing(farthestLeft);
		}
		else if (mKey == S_KEY)
		{
			PhysicsData data;
			data.vel = 0;
			data.acc = 0;
			gpGameApp->getUnitManager()->getPlayerUnit()->getPhysicsComponent()->setData(data);

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			Vector2D farthestDown(playerPos.getX(), 767.0f);

			bool test = clearPathRaycast(playerPos, farthestDown);

			cout << test << endl;
			//TODO: raycast for position data to send to pathfinder 

			//768 is max screen height, width - 1024
			//toY - raycast right until blocking path if none, then path to screen bounds
			if (test)
				initializePlayerPathing(farthestDown);
		}
		else if (mKey == D_KEY) //GO RIGHT
		{
			PhysicsData data;
			data.vel = 0;
			data.acc = 0;
			gpGameApp->getUnitManager()->getPlayerUnit()->getPhysicsComponent()->setData(data);

			Vector2D playerPos = gpGameApp->getUnitManager()->getPlayerUnit()->getPositionComponent()->getPosition();
			
			Vector2D farthestRight(1023.0f, playerPos.getY());

			bool test = clearPathRaycast(playerPos, farthestRight);
			
			cout << test << endl;
			//TODO: raycast for position data to send to pathfinder 

			//768 is max screen height, width - 1024
			//toY - raycast right until blocking path if none, then path to screen bounds
			if(test)
				initializePlayerPathing(farthestRight);
		}

		/*if (mKey == 4)
		{
			//delete exisiting units
			while(gpGameApp->getUnitManager()->size() > 0)
				gpGameApp->getUnitManager()->deleteRandomUnit();

			//clear gpPaths
			int size = gpGameApp->gpPaths.size();
			for (int i = 0; i < size; i++)
			{
				delete gpGameApp->gpPaths[0];
				gpGameApp->gpPaths.erase(gpGameApp->gpPaths.begin());
			}

			//spawn a new set of units
			for (int i = 0; i < 10; i++)
			{
				cout << "NEW UNIT " << i << endl;
				Sprite* tmpSpr = gpGameApp->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID);
				Unit* newUnit = gpGameApp->getUnitManager()->createRandomUnit(*tmpSpr);

				float x = newUnit->getPositionComponent()->getPosition().getX();
				float y = newUnit->getPositionComponent()->getPosition().getY();

				//check if unit is within or adjacent to a wall tile, randomize its position until it is not
				int squareIndex = gpGameApp->getGrid()->getSquareIndexFromPixelXY(x, y);
				std::vector<int> adjacencies = gpGameApp->getGrid()->getAdjacentIndices(squareIndex);

				for (unsigned int adjIndex = 0; adjIndex < adjacencies.size(); adjIndex++)
				{
					while (gpGameApp->getGrid()->getValueAtIndex(adjacencies[adjIndex]) == BLOCKING_VALUE)
					{
						cout << "WALL" << endl;
						newUnit->randomizePosition();

						x = newUnit->getPositionComponent()->getPosition().getX();
						y = newUnit->getPositionComponent()->getPosition().getY();
						
						squareIndex = gpGameApp->getGrid()->getSquareIndexFromPixelXY(x, y);
						
						adjacencies = gpGameApp->getGrid()->getAdjacentIndices(squareIndex);
						adjIndex = 0;

					}
				}
			}
		}*/
	}

	
}

bool KeyDownMessage::clearPathRaycast(Vector2D fromPos, Vector2D toPos)
{
	GameApp* pGameApp = dynamic_cast<GameApp*>(gpGame);
	float previousX, previousY;
	Vector2D direction;
	bool result = true;

	//fromPos = pGameApp->getGrid()->getULCornerOfSquare(startCastNode->getId());
	//toPos = pGameApp->getGrid()->getULCornerOfSquare(nextNode->getId());

	direction = toPos - fromPos;

	float posX = fromPos.getX();
	float posY = fromPos.getY();

	for (size_t i = 0; i < 100 /*mRAY_ITERATORS*/; i++)
	{
		bool pathBlocked = pGameApp->getGrid()->getValueAtPixelXY((int)posX, (int)posY) == BLOCKING_VALUE;

		if (pathBlocked)
		{
			result = false;
			break;
		}
		else
		{
			previousX = posX;
			previousY = posY;
		}

		//shoot raycast
		posX = posX + (direction.getX() / 100);
		posY = posY + (direction.getY() / 100);
	}

	return result;
}
