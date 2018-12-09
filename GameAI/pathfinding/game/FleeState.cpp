#include "Game.h"
#include "FleeState.h"
#include <iostream>

using namespace std;

void FleeState::onEntrance()
{
	cout << "\nEntering TickState id:" << mID << endl;
}

void FleeState::onExit()
{
	cout << "\nexitting TickState id:" << mID << endl;
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
	cout << "Tick...\n";
	return NULL;//no transition
}