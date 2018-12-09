#pragma once
#include "state machine/StateMachine.h"

class WanderState : public StateMachineState
{
public:
	WanderState(const SM_idType& id) :StateMachineState(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
private:

};