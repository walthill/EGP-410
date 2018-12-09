#pragma once
#include "state machine/StateMachine.h"
#include "../game/component steering/Unit.h"

class ChaseState : public StateMachineState
{
public:
	ChaseState(const SM_idType& id) :StateMachineState(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

	void updateTarget(Unit* target);

private:
	Unit* mTarget;
};