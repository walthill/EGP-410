#include "Game.h"
#include "EmptyState.h"
#include <iostream>

using namespace std;

void EmptyState::onEntrance()
{
	//nothing
}

void EmptyState::onExit()
{
	//don't even worry about it
}

StateTransition* EmptyState::update()
{
	return NULL;//no transition
}