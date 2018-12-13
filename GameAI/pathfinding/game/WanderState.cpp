#include "Game.h"
#include "WanderState.h"
#include <iostream>
#include "GraphicsSystem.h"
#include "../game/component steering/Unit.h"
#include "../game/component steering/UnitManager.h"
#include "../game/GridPathfinder.h"
#include "Vector2D.h"
#include "PathToMessage.h"
#include "GameMessageManager.h"
#include "../game/component steering/PositionComponent.h"
#include "Grid.h"
#include "Path.h"
#include "Node.h"
#include "UnitStateMachine.h"

using namespace std;

void WanderState::onEntrance()
{
	cout << "wander" << endl;
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
	
	//Health transitions =================================



	//Player transitions =================================

	float distance = (pUnit->mUnitStateMachine->getPlayer()->getPositionComponent()->getPosition() - pUnit->getPositionComponent()->getPosition()).getLength();

	if (distance < aggroRange && !pUnit->mUnitStateMachine->getPlayer()->mUnitStateMachine->isPowered())//player in range and not powered
	{
		pUnit->mUnitStateMachine->updateTarget(pUnit->mUnitStateMachine->getPlayer());
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(CHASE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	if (distance < aggroRange && gpGameApp->getUnitManager()->getPlayerUnit()->mUnitStateMachine->isPowered())//player in range and powered
	{
		pUnit->mUnitStateMachine->updateTarget(pUnit->mUnitStateMachine->getPlayer());
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(FLEE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	
	
	
	

	//destination reached==============================
	
	if (pUnit->getNumPathNodes() == 0)
	{
		onEntrance();
	}
	if (gpGameApp->getGrid()->getSquareIndexFromPixelXY(pUnit->getPositionComponent()->getPosition().getX(),
		pUnit->getPositionComponent()->getPosition().getY()) == pUnit->getPath()->peekNextNode()->getId())
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

void WanderState::setAggroRange(int range)
{
	aggroRange = range;
}