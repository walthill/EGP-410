#include "Player.h"
#include "Collider.h"
#include "../game/component steering/Unit.h"

Player::Player()
{
	playerUnit = NULL;
}

Player::~Player()
{
}

void Player::process(std::vector<Unit*> mUnitMap)
{
	//update collider to follow unit
	playerUnit->getCollider()->setX(playerUnit->getPositionComponent()->getPosition().getX());
	playerUnit->getCollider()->setY(playerUnit->getPositionComponent()->getPosition().getY());

	//perform collision checks
	for (size_t i = 0; i < mUnitMap.size(); i++)
	{
		if (playerUnit->checkCollision(mUnitMap[i]->getCollider())
			&& mUnitMap[i]->getCollider()->getTag() == COIN)
		{
			cout << "X: " << mUnitMap[i]->getPositionComponent()->getPosition().getX() << endl;
			cout << "Y: " << mUnitMap[i]->getPositionComponent()->getPosition().getY() << endl;
			cout << "COLLUSION" << endl;

			//destroy coin, increase score
		}
		else
		{
		}
	}


	/*Vector2D currentLocation = playerUnit->getPositionComponent()->getPosition();
	Vector2D targetLoc;
	targetLoc.setX(currentLocation.getX() + 16);
	targetLoc.setY(currentLocation.getY() + 16);

	Vector2D direction = targetLoc - currentLocation;
	float directionToCoin = direction.getLength();

	//

	if (directionToCoin < coinCaptureRadius)
	{
		//increase score, delete coin
	}*/


}

void Player::hookPlayerUnit(Unit* playersUnit)
{
	playerUnit = playersUnit; 
}