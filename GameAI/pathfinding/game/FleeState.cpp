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
	cout << "flee" << endl;
	frames = 0;
	pUnit->mUnitStateMachine->setPowered(false);
}

void FleeState::onExit()
{
	
	//nothing real to do here
}

StateTransition* FleeState::update()
{
	
	
	if (gpGameApp->isPlayerPoweredUp())
	{
		float distance = (pUnit->mUnitStateMachine->getPlayer()->getPositionComponent()->getPosition() - pUnit->getPositionComponent()->getPosition()).getLength();
		if (distance < aggroRange)
		{
			

			frames++;

			if (frames / 30 > 1)
			{
				cout << "damage" << endl;
				pUnit->mUnitStateMachine->setHealth(pUnit->mUnitStateMachine->getHealth() - 26);
			}
		}
	}
	else
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}

	}

	//Health
	if (pUnit->mUnitStateMachine->getHealth() <= 0)
	{
		//gpGameApp->getUnitManager()->deleteUnit(pUnit->getUnitID());
		pUnit->canDelete = true;
	}
	
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