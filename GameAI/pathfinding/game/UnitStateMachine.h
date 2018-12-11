#pragma once
#include "state machine/StateMachine.h"
#include "IdleState.h"
#include "WanderState.h"
#include "ChaseState.h"
#include "FleeState.h"
#include "../game/component steering/Unit.h"

class UnitStateMachine :public StateMachine
{
	
public:
	UnitStateMachine(int machineType, int unitID);

	//state machine
	//StateMachine* pStateMachine;
	
	//states
	StateMachineState* pIdleState;
	StateMachineState* pWanderState;
	StateMachineState* pChaseState;
	StateMachineState* pFleeState;

	//transitions
	StateTransition* pToIdleTrans;
	StateTransition* pToWanderTrans;
	StateTransition* pToChaseTrans;
	StateTransition* pToFleeTrans;

	void updateTarget(Unit* target);

protected:

};