#include "UnitStateMachine.h"
#include "ChaseState.h"
#include "FleeState.h"
#include "WanderState.h"
#include "EmptyState.h"
#include "GameApp.h"
#include "../game/component steering/UnitManager.h"


UnitStateMachine::UnitStateMachine(int machineType, int unitID)
{
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	Unit* pUnit = gpGameApp->getUnitManager()->getUnit(unitID);

	player = gpGameApp->getUnitManager()->getPlayerUnit();

	if (machineType == 0)
	{
		pIdleState = new EmptyState(0);
		this->addState(pIdleState);
		this->setInitialStateID(0);
	}

	if (machineType == 1)
	{
		//states
		pIdleState = new IdleState(0, 10);
		pWanderState = new WanderState(1, pUnit);
		pChaseState = new ChaseState(2, pUnit);
		pFleeState = new FleeState(3, pUnit);


		//transitions
		pToIdleTrans = new StateTransition(IDLE_TRANSITION, 0);
		pToWanderTrans = new StateTransition(WANDER_TRANSITION, 1);
		pToChaseTrans = new StateTransition(CHASE_TRANSITION, 2);
		pToFleeTrans = new StateTransition(FLEE_TRANSITION, 3);

		//add Idle transitions
		pIdleState->addTransition(pToWanderTrans);
		pIdleState->addTransition(pToChaseTrans);
		pIdleState->addTransition(pToFleeTrans);

		//add Wander transitions
		pWanderState->addTransition(pToIdleTrans);
		pWanderState->addTransition(pToChaseTrans);
		pWanderState->addTransition(pToFleeTrans);

		//add Chase transitions
		pChaseState->addTransition(pToIdleTrans);

		//add Flee transitions
		pFleeState->addTransition(pToIdleTrans);

		//add states to state machine
		this->addState(pIdleState);
		this->addState(pWanderState);
		this->addState(pChaseState);
		this->addState(pFleeState);

		//set default dtate
		this->setInitialStateID(0);
	}
	if(machineType == 2)//dummy state for coins
	{
		pIdleState = new EmptyState(0);
		this->addState(pIdleState);
		this->setInitialStateID(0);
	}
}

bool UnitStateMachine::isPowered()
{
	return powered;
}

void UnitStateMachine::setPowered(bool power)
{
	powered = power;
}

void UnitStateMachine::updateTarget(Unit* target)
{
	ChaseState* pChaseState = dynamic_cast<ChaseState*>(pChaseState);
	pChaseState->updateTarget(target);
	FleeState* pFleeState = dynamic_cast<FleeState*>(pFleeState);
	pFleeState->updateTarget(target);
	WanderState* pWanderState = dynamic_cast<WanderState*>(pWanderState);
	pWanderState->updateTarget(target);
}

void UnitStateMachine::setAggroRange(int range)
{
	ChaseState* pChaseState = dynamic_cast<ChaseState*>(pChaseState);
	pChaseState->setAggroRange(range);
	WanderState* pWanderState = dynamic_cast<WanderState*>(pWanderState);
	pWanderState->setAggroRange(range);
	FleeState* pFleeState = dynamic_cast<FleeState*>(pFleeState);
	pFleeState->setAggroRange(range);
}