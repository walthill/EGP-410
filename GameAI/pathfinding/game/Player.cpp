#include "Player.h"
#include "Collider.h"
#include "../game/component steering/Unit.h"
#include "component steering/UnitManager.h"
#include "ScoreboardContent.h"
#include "GameApp.h"

Player::Player()
{
	playerUnit = NULL;
	gameHandle = dynamic_cast<GameApp*>(gpGame);
}

Player::~Player()
{
}

void Player::process(std::vector<Unit*> &unitMap)
{
	performCollisionChecks(unitMap);
}

void Player::performCollisionChecks(std::vector<Unit*> &unitMap)
{
	//perform collision checks
	for (size_t i = 0; i < unitMap.size(); i++)
	{
		bool hasCollided = playerUnit->checkCollision(unitMap[i]->getCollider());

		if (hasCollided)
		{
			ColliderType otherTag = unitMap[i]->getCollider()->getTag();;

			if (otherTag == COIN)
			{
				//destroy coin, increase score
				int unitId = unitMap[i]->getUnitID();

				gameHandle->getUnitManager()->deleteUnit(unitId);
				gameHandle->addCoinScore();
			}
			else if (otherTag == HEALTH_POWER)
			{
				//destroy coin, increase health
				int unitId = unitMap[i]->getUnitID();

				gameHandle->getUnitManager()->deleteUnit(unitId);
			}
			else if (otherTag == POWERUP)
			{
				//destroy coin, POWERUPPPP
				int unitId = unitMap[i]->getUnitID();

				gameHandle->getUnitManager()->deleteUnit(unitId);
				gameHandle->addPowerupScore();
			}
		}
	}
}

void Player::hookPlayerUnit(Unit* playersUnit)
{
	playerUnit = playersUnit; 
}