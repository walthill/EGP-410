#include "UnitStateMachine.h"

UnitStateMachine::UnitStateMachine()
{
	//state machine
	StateMachine* pStateMachine = new StateMachine();

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

	//add Transitions
	pIdleState->addTransition(pToIdleTrans);
	pWanderState->addTransition(pToWanderTrans);
	pChaseState->addTransition(pToChaseTrans);
	pFleeState->addTransition(pToFleeTrans);

	//add states to state machine
	pStateMachine->addState(pIdleState);
	pStateMachine->addState(pWanderState);
	pStateMachine->addState(pChaseState);
	pStateMachine->addState(pFleeState);

	//set default dtate
	pStateMachine->setInitialStateID(0);
}

UnitStateMachine::~UnitStateMachine()
{
	delete pStateMachine;

	delete pIdleState;
	delete pWanderState;
	delete pChaseState;
	delete pFleeState;

	delete pToIdleTrans;
	delete pToWanderTrans;
	delete pToChaseTrans;
	delete pToFleeTrans;
}
