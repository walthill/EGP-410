#include "Game.h"
#include "WanderState.h"
#include <iostream>
#include "GraphicsSystem.h"
#include "../game/component steering/Unit.h"
#include "../game/component steering/UnitManager.h"
#include "../game/GridPathfinder.h"
#include "GameApp.h"
#include "Vector2D.h"
#include "PathToMessage.h"
#include "GameMessageManager.h"
#include "../game/component steering/PositionComponent.h"
#include "Grid.h"
#include "Path.h"
#include "Node.h"

using namespace std;

void WanderState::onEntrance()
{
	
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	
	//pick a random point and pathfind to it
	int posX = rand() % gpGame->getGraphicsSystem()->getWidth();
	int posY = rand() % gpGame->getGraphicsSystem()->getHeight();
	int index = gpGameApp->getGrid()->getSquareIndexFromPixelXY(posX, posY);
	while (gpGameApp->getGrid()->getValueAtIndex(index) == BLOCKING_VALUE)
	{
		posX = rand() % gpGame->getGraphicsSystem()->getWidth();
		posY = rand() % gpGame->getGraphicsSystem()->getHeight();
		index = gpGameApp->getGrid()->getSquareIndexFromPixelXY(posX, posY);
	}
	cout << "x: " << posX << " y: " << posY << endl;
	
	cout << gpGameApp->getGrid()->getValueAtIndex(index) << endl;
	int playerIndex = gpGameApp->getGrid()->getSquareIndexFromPixelXY(pUnit->getPositionComponent()->getPosition().getX(), pUnit->getPositionComponent()->getPosition().getY());
	gpGameApp->mpMessageManager->addMessage(new PathToMessage(pUnit, gpGameApp->getGrid()->getULCornerOfSquare(playerIndex), gpGameApp->getGrid()->getULCornerOfSquare(index)), 0);
	cout << "path" << endl;
	
}

void WanderState::onExit()
{
	
}

StateTransition* WanderState::update()
{
	//override transition to chase/flee if player is near and powered/not powered
	cout << pUnit->getPath() << endl;
	if (pUnit->getNumPathNodes() == 0)
	{
		onEntrance();
	}

		GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
		if (gpGameApp->getGrid()->getSquareIndexFromPixelXY(pUnit->getPositionComponent()->getPosition().getX(), 
			pUnit->getPositionComponent()->getPosition().getY()) == pUnit->getPath()->peekNextNode()->getId())//destination reached
		{
			//find the right transition
			map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
			if (iter != mTransitions.end())//found?
			{
				StateTransition* pTransition = iter->second;
				return pTransition;
			}
		}
	
	
	return NULL;//no transition
}

void WanderState::updateTarget(Unit* target)
{
	pTarget = target;
}