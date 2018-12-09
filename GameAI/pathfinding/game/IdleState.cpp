#include "Game.h"
#include "IdleState.h"
#include <iostream>

using namespace std;

void IdleState::onEntrance()
{
	frames = 0;
	cout << "enter idle state" << endl;
	//mStartingCount = gpGame->getFrameCount();//set the starting count as we just entered
}

void IdleState::onExit()
{
	cout << "exit idle state" << endl;
	//nothing real to do here
}

StateTransition* IdleState::update()
{
	frames++;

	//find out if enough time has passed to transitions
	if ((frames / 30) > maxTime)
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(WANDER_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			cout << "transition" << endl;
			return pTransition;
			
		}
	}
	//cout << "Tick...\n";
	return NULL;//no transition
}