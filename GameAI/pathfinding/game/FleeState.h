#pragma once
#include "state machine/StateMachine.h"
#include "../game/component steering/Unit.h"

class FleeState : public StateMachineState
{
public:
	FleeState(const SM_idType& id) :StateMachineState(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

	void updateTarget(Unit* target);

private:

	Unit* mTarget;

};