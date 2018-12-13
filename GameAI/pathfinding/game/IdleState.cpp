#include "Game.h"
#include "IdleState.h"
#include <iostream>
#include "../game/component steering/Unit.h"
#include "UnitStateMachine.h"
#include "../game/component steering/UnitManager.h"
#include "../game/component steering/PositionComponent.h"

using namespace std;

void IdleState::onEntrance()
{
	cout << "idle" << endl;
	frames = 0;
	pUnit->mUnitStateMachine->setPowered(false);
}

void IdleState::onExit()
{
	//nothing real to do here
}

StateTransition* IdleState::update()
{
	frames++;


	//Player transitions =================================

	float distance = (pUnit->mUnitStateMachine->getPlayer()->getPositionComponent()->getPosition() - pUnit->getPositionComponent()->getPosition()).getLength();

	if (distance < aggroRange && !gpGameApp->isPlayerPoweredUp())//player in range and not powered
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
	if (distance < aggroRange && gpGameApp->isPlayerPoweredUp())//player in range and powered
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


	//transition when timer is done =======================

	if ((frames / 30) > maxTime)
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(WANDER_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			cout << "transition" << endl;
			return pTransition;
			
		}
	}
	
	return NULL;//no transition
}