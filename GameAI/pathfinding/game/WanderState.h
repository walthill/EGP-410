#pragma once
#include "state machine/StateMachine.h"
#include "../game/component steering/Unit.h"
#include "GameApp.h"

class WanderState : public StateMachineState
{
public:
	WanderState(const SM_idType& id, Unit* unit) :StateMachineState(id), pUnit(unit){};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();

	void updateTarget(Unit* target);
	void setAggroRange(int range);
private:
	Unit* pTarget;
	Unit* pUnit;
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	float aggroRange = 20;
};