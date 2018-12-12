#pragma once

#include <Trackable.h>
#include <DeanLibDefines.h>
#include <MemoryPool.h>
#include <vector>
#include <map>
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "Unit.h"

class Unit;
class Sprite;
struct PositionData;
struct PhysicsData;

const UnitID PLAYER_UNIT_ID = 0;

enum unitType
{
	PLAYER_UNIT = 0,
	ENEMY_UNIT = 1,
	COIN_UNIT = 2,

};


class UnitManager : public Trackable
{
public:
	UnitManager(Uint32 maxSize);
	~UnitManager();

	Unit* createUnit(unitType unitType, const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA, const UnitID& id = INVALID_UNIT_ID);
	Unit* createPlayerUnit(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = ZERO_POSITION_DATA, const PhysicsData& physicsData = ZERO_PHYSICS_DATA);
	Unit* createRandomUnit(unitType unitType, const Sprite& sprite);
	Unit* createRandomUnit(unitType unitType, const Sprite& sprite, const UnitID& targetId);
	std::vector<Unit*> getAllUnits();
	Unit* getUnit(const UnitID& id) const;
	void deleteUnit(const UnitID& id);
	void deleteRandomUnit();
	bool hasNewUnit();
	void drawAll() const;
	void updateAll(float elapsedTime);
	int size();


	Unit* getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };

private:
	int mCallCount;
	bool mIsNewUnit;
	static UnitID msNextUnitID;
	MemoryPool mPool;
	std::map<UnitID, Unit*> mUnitMap;
};

