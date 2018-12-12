#pragma once
#include <vector>
#include "Trackable.h"
#include "../game/component steering/Unit.h"

class EnemyPool: public Trackable
{
public:
	EnemyPool();
	~EnemyPool();

private:
	Unit** enemies;
	int totalEnemies = 0;
};