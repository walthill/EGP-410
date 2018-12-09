#include "Game.h"
#include "IdleState.h"
#include <iostream>

using namespace std;

void IdleState::onEntrance()
{
	cout << "\nEntering TickState id:" << mID << endl;
	//mStartingCount = gpGame->getFrameCount();//set the starting count as we just entered
}

void IdleState::onExit()
{
	cout << "\nexitting TickState id:" << mID << endl;
	//nothing real to do here
}

StateTransition* IdleState::update()
{
	////find out if enough time has passed to transitions
	//if ((gpGame->getFrameCount() - mStartingCount) >= mFireCount)
	//{
	//	//find the right transition
	//	map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(WANDER_TRANSITION);
	//	if (iter != mTransitions.end())//found?
	//	{
	//		StateTransition* pTransition = iter->second;
	//		return pTransition;
	//	}
	//}
	cout << "Tick...\n";
	return NULL;//no transition
}