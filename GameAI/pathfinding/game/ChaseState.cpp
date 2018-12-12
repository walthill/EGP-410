#include "Game.h"
#include "ChaseState.h"
#include <iostream>
#include "Grid.h"
#include "PathToMessage.h"
#include "GameMessageManager.h"
#include "Vector2D.h"
#include "UnitStateMachine.h"
#include "Path.h"
#include "Node.h"
#include "../game/component steering/UnitManager.h"


using namespace std;

void ChaseState::onEntrance()
{
	frames = 0;
	gpGameApp->mpMessageManager->addMessage(new PathToMessage(pUnit, pUnit->getPositionComponent()->getPosition(), mTarget->getPositionComponent()->getPosition()), 0);
}

void ChaseState::onExit()
{
	
}

StateTransition* ChaseState::update()
{
	//health
	if (pUnit->mUnitStateMachine->getHealth() <= 0)
	{
		gpGameApp->getUnitManager()->deleteUnit(pUnit->getUnitID());
	}
	++frames;

	if (frames / 30 > 2)//pathfind to target every certain time
	{
		frames = 0;
		gpGameApp->mpMessageManager->addMessage(new PathToMessage(pUnit, pUnit->getPositionComponent()->getPosition(), mTarget->getPositionComponent()->getPosition()), 0);
		
	}
	

	//player transitions ==================================

	if (mTarget->getUnitID() == 0 && (pUnit->getPositionComponent()->getPosition() - mTarget->getPositionComponent()->getPosition()).getLength() > aggroRange)//player left aggro
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(WANDER_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	if (mTarget->getUnitID() == 0 && mTarget->mUnitStateMachine->isPowered())//player becomes powered
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(FLEE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	

	//arrived ========================================
	if (pUnit->getNumPathNodes() == 0)
	{
		onEntrance();
	}
	if (mTarget != pUnit->mUnitStateMachine->getPlayer())
	{
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
	}


	return NULL;//no transition
}

void ChaseState :: updateTarget(Unit* target)
{
	mTarget = target;
}

void ChaseState::setAggroRange(int range)
{
	aggroRange = range;
}