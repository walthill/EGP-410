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
		powered = false;
	}

	if (machineType == 1)
	{
		//states
		pIdleState = new IdleState(0, 10, pUnit);
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

		powered = true;
	}
	if(machineType == 2)//dummy state for coins
	{
		pIdleState = new EmptyState(0);
		this->addState(pIdleState);
		this->setInitialStateID(0);
		powered = false;
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
	ChaseState* gpChaseState = dynamic_cast<ChaseState*>(pChaseState);
	gpChaseState->updateTarget(target);
	FleeState* gpFleeState = dynamic_cast<FleeState*>(pFleeState);
	gpFleeState->updateTarget(target);
	WanderState* gpWanderState = dynamic_cast<WanderState*>(pWanderState);
	gpWanderState->updateTarget(target);
}

void UnitStateMachine::setAggroRange(int range)
{
	ChaseState* gpChaseState = dynamic_cast<ChaseState*>(pChaseState);
	gpChaseState->setAggroRange(range);
	WanderState* gpWanderState = dynamic_cast<WanderState*>(pWanderState);
	gpWanderState->setAggroRange(range);
	FleeState* gpFleeState = dynamic_cast<FleeState*>(pFleeState);
	gpFleeState->setAggroRange(range);
}