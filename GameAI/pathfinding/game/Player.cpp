#include "Player.h"
#include "Collider.h"
#include "../game/component steering/Unit.h"
#include "component steering/UnitManager.h"
#include "ScoreboardContent.h"
#include "GameApp.h"
#include "../game/component steering/Unit.h"
#include "../game/component steering/UnitManager.h"

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

	if (mHealth <= 0)
	{
		gameHandle->lose();
	}
}

void Player::damage()
{
	mHealth -= 20;
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
				mHealth += gameHandle->heal();
			}
			else if (otherTag == POWERUP)
			{
				//destroy coin, POWERUPPPP
				int unitId = unitMap[i]->getUnitID();
				cout << "powered" << endl;
				gameHandle->getUnitManager()->deleteUnit(unitId);
				gameHandle->addPowerupScore();
				gameHandle->PlayerPowerUp();
			}
		}
	}
}

void Player::hookPlayerUnit(Unit* playersUnit)
{
	playerUnit = playersUnit; 
}