#pragma once
#include "state machine/StateMachine.h"
#include "GameApp.h"

class IdleState : public StateMachineState
{
public:
	IdleState(const SM_idType& id, int fireCount, Unit* unit) :StateMachineState(id), mFireCount(fireCount), pUnit(unit) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();


private:
	int mFireCount;//how many frames need to pass from start until transition
	int mStartingCount;//when did we start?
	int frames;
	int maxTime = 5;

	Unit* pUnit;
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	float aggroRange = 200;
};