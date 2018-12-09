#include "UnitStateMachine.h"
#include "ChaseState.h"
#include "FleeState.h"

UnitStateMachine::UnitStateMachine(int machineType)
{
	//state machine
	//StateMachine* pStateMachine = new StateMachine();

	//states
	pIdleState = new IdleState(0, 10);
	pWanderState = new WanderState(1);
	pChaseState = new ChaseState(2);
	pFleeState = new FleeState(3);

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

void UnitStateMachine::updateTarget(Unit* target)
{
	ChaseState* pChaseState = dynamic_cast<ChaseState*>(pChaseState);
	pChaseState->updateTarget(target);
	FleeState* pFleeState = dynamic_cast<FleeState*>(pFleeState);
	pFleeState->updateTarget(target);
		
}