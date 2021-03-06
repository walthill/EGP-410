#include "EnemyPool.h"
#include "GameApp.h"
#include <vector>
#include "../game/component steering/UnitManager.h"
#include "SpriteManager.h"

EnemyPool::EnemyPool()
{
	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);
	totalEnemies = gpGameApp->totalEnemies;
	enemies = new Unit*[totalEnemies];
	
	Sprite* enemySprite = gpGameApp->getSpriteManager()->getSprite(ENEMY_SPRITE_ID);
	for (int i = 0; i < totalEnemies; ++i)
	{
		Unit* pUnit = gpGameApp->getUnitManager()->createRandomUnit(ENEMY_UNIT, *enemySprite);
		
		pUnit->getCollider()->initCollider(pUnit->getPositionComponent()->getPosition().getX(),
																	pUnit->getPositionComponent()->getPosition().getY(),
																	16, 16, ENEMY, pUnit);
		enemies[i] = pUnit;
	}
}

EnemyPool::~EnemyPool()
{
	delete enemies;
}