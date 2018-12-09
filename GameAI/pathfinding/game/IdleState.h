#pragma once
#include "state machine/StateMachine.h"

class IdleState : public StateMachineState
{
public:
	IdleState(const SM_idType& id, int fireCount) :StateMachineState(id), mFireCount(fireCount) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
private:
	int mFireCount;//how many frames need to pass from start until transition
	int mStartingCount;//when did we start?
	int frames;
	int maxTime = 33;
};