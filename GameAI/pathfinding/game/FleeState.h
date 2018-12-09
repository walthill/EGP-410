#pragma once
#include "state machine/StateMachine.h"

class FleeState : public StateMachineState
{
public:
	FleeState(const SM_idType& id) :StateMachineState(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
private:

};