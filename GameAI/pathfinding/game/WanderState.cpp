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

using namespace std;

void WanderState::onEntrance()
{
	
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	
	//pick a random point and pathfind to it
	int posX = rand() % gpGame->getGraphicsSystem()->getWidth();
	int posY = rand() % gpGame->getGraphicsSystem()->getHeight();
	
	
	gpGameApp->mpMessageManager->addMessage(new PathToMessage(pUnit, Vector2D(pUnit->getPositionComponent()->getPosition()), Vector2D(posX, posY)), 1);
}

void WanderState::onExit()
{
	
}

StateTransition* WanderState::update()
{
	//override transition to chase/flee if player is near and powered/not powered

	if (pUnit->getNumPathNodes() > 0)
	{
		
		if (pUnit->getPath()->peekNextNode() == pUnit->getPath()->peekNode(pUnit->getNumPathNodes() - 1))//destination reached
		{
			//find the right transition
			map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
			if (iter != mTransitions.end())//found?
			{
				StateTransition* pTransition = iter->second;
				return pTransition;
			}
		}
	}
	
	return NULL;//no transition
}

void WanderState::updateTarget(Unit* target)
{
	pTarget = target;
}