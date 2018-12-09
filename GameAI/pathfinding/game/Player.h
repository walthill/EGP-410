#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <Trackable.h>
//#include "../game/component steering/Unit.h"

class Unit;
class Collider;

class Player : public Trackable
{
	private:
		Unit* playerUnit;
		
		

		int health;
	
		float coinCaptureRadius;

	public:
		Player();
		~Player();

		void process(std::vector<Unit*> mUnitMap);

		void hookPlayerUnit(Unit* playersUnit);
		Unit* getPlayerUnit() { return playerUnit; };
};

#endif // !PLAYER_H
