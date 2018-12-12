#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <Trackable.h>

class Unit;
class Collider;
class GameApp;

class Player : public Trackable
{
	private:
		Unit* playerUnit;
		GameApp* gameHandle;

		int health;
		float coinCaptureRadius;

	public:
		Player();
		~Player();

		void process(std::vector<Unit*> &unitMap);
		void performCollisionChecks(std::vector<Unit*> &unitMap);


		void hookPlayerUnit(Unit* playersUnit);
		Unit* getPlayerUnit() { return playerUnit; };
};

#endif // !PLAYER_H
