#include "Game.h"
#include "FleeState.h"
#include <iostream>

using namespace std;

void FleeState::onEntrance()
{
	
}

void FleeState::onExit()
{
	
	//nothing real to do here
}

StateTransition* FleeState::update()
{
	////find out if enough time has passed to transitions
	//if ((gpGame->getFrameCount() - mStartingCount) >= mFireCount)
	//{
	//	//find the right transition
	//	map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(KABOOM_TRANSITION);
	//	if (iter != mTransitions.end())//found?
	//	{
	//		StateTransition* pTransition = iter->second;
	//		return pTransition;
	//	}
	//}
	
	return NULL;//no transition
}

void FleeState::updateTarget(Unit* target)
{
	mTarget = target;
}