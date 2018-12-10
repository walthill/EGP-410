#pragma once
#include "state machine/StateMachine.h"
#include "../game/component steering/Unit.h"

class WanderState : public StateMachineState
{
public:
	WanderState(const SM_idType& id, Unit* unit) :StateMachineState(id), pUnit(unit){};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

	void updateTarget(Unit* target);
private:
	Unit* pTarget;
	Unit* pUnit;
};