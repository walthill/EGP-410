#pragma once
#include "state machine/StateMachine.h"

class EmptyState : public StateMachineState
{
public:
	EmptyState(const SM_idType& id) :StateMachineState(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
};