#include "Game.h"
#include "ChaseState.h"
#include <iostream>
#include "Grid.h"
#include "PathToMessage.h"
#include "GameMessageManager.h"
#include "Vector2D.h"
#include "UnitStateMachine.h"
#include "Path.h"
#include "Node.h"
#include "../game/component steering/UnitManager.h"
#include "../game/component steering/PositionComponent.h"
#include "GridGraph.h"


using namespace std;

void ChaseState::onEntrance()
{
	cout << "idle" << endl;
	frames = 0;
	gpGameApp->mpMessageManager->addMessage(new PathToMessage(pUnit, pUnit->getPositionComponent()->getPosition(), mTarget->getPositionComponent()->getPosition()), 0);
	pUnit->mUnitStateMachine->setPowered(true);
}

void ChaseState::onExit()
{
	
}

StateTransition* ChaseState::update()
{
	
	++frames;

	if (frames / 30 > 2)//pathfind to target every certain time
	{
		frames = 0;
		gpGameApp->mpMessageManager->addMessage(new PathToMessage(pUnit, pUnit->getPositionComponent()->getPosition(), mTarget->getPositionComponent()->getPosition()), 0);
		
	}
	

	//player transitions ==================================

	if (mTarget->getUnitID() == 0 && (pUnit->getPositionComponent()->getPosition() - mTarget->getPositionComponent()->getPosition()).getLength() > aggroRange)//player left aggro
	{
		cout << "out of chase" << endl;
		Path tempPath = Path();
		tempPath.addNode(gpGameApp->getGridGraph()->getNode(gpGameApp->getGrid()->getSquareIndexFromPixelXY(pUnit->getPositionComponent()->getPosition().getX(), 
																											pUnit->getPositionComponent()->getPosition().getY())));

		pUnit->setPath(tempPath);
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			cout << "transition out" << endl;
			return pTransition;
		}
	}

	if (mTarget->getUnitID() == 0 && gpGameApp->isPlayerPoweredUp())//player becomes powered
	{
		//find the right transition
		map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(FLEE_TRANSITION);
		if (iter != mTransitions.end())//found?
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	

	//arrived ========================================
	
	if (mTarget != pUnit->mUnitStateMachine->getPlayer())
	{
		if (pUnit->getPath()->getNumNodes() == 0)
		{
			//find the right transition
			map<TransitionType, StateTransition*>::iterator iter = mTransitions.find(IDLE_TRANSITION);
			if (iter != mTransitions.end())//found?
			{
				StateTransition* pTransition = iter->second;
				return pTransition;
			}
		}
	}


	return NULL;//no transition
}

void ChaseState :: updateTarget(Unit* target)
{
	mTarget = target;
}

void ChaseState::setAggroRange(int range)
{
	aggroRange = range;
}