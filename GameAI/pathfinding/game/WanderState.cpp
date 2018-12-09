#include "Game.h"
#include "WanderState.h"
#include <iostream>

using namespace std;

void WanderState::onEntrance()
{
	//pick a random point and pathfind to it
}

void WanderState::onExit()
{
	//nothing real to do here
}

StateTransition* WanderState::update()
{
	//find out if enough time has passed to transition

	if (false)//destination reached
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	
	return NULL;//no transition
}