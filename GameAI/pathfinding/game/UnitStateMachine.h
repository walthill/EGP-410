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
	StateMachineState* pIdleState = NULL;
	StateMachineState* pWanderState = NULL;
	StateMachineState* pChaseState = NULL;
	StateMachineState* pFleeState = NULL;

	//transitions
	StateTransition* pToIdleTrans = NULL;
	StateTransition* pToWanderTrans = NULL;
	StateTransition* pToChaseTrans = NULL;
	StateTransition* pToFleeTrans = NULL;

	void updateTarget(Unit* target);
	bool isPowered();
	void setPowered(bool power);
	void setAggroRange(int range);
	Unit* getPlayer() { return player; };
	void setHealth(int newhealth) { health = newhealth; };
	int getHealth() { return health; };

protected:
	int health = 100;
	bool powered;
	int aggroRange;
	Unit* player;
};