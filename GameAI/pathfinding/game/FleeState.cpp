#include "Game.h"
#include "FleeState.h"
#include <iostream>
#include "../game/component steering/Unit.h"
#include "UnitStateMachine.h"
#include "../game/component steering/UnitManager.h"
#include "../game/component steering/PositionComponent.h"

using namespace std;

void FleeState::onEntrance()
{
	frames = 0;
}

void FleeState::onExit()
{
	
	//nothing real to do here
}

StateTransition* FleeState::update()
{
	if (gpGameApp.isPlayerPoweredUp())
	{
		pUnit->mUnitStateMachine->setPowered(false);

		frames++;

		if (frames / 30 > 1)
		{
			pUnit->mUnitStateMachine->setHealth(pUnit->mUnitStateMachine->getHealth() - 26);
		}
	}
	////find out if enough time has passed to transitions
	//if ((gpGame->getFrameCount() - mStartingCount) >= mFireCount)
	//{
	//	//find the right transition
	//	map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(KABOOM_TRANSITION);
	//	if (iter != mTransitions.end())//found?
	//	{
	//		StateTransition* pTransition = iter->second;
	//		return pTransition;
	//	}
	//}
	
	return NULL;//no transition
}

void FleeState::updateTarget(Unit* target)
{
	mTarget = target;
}

void FleeState::setAggroRange(int range)
{
	aggroRange = range;
}