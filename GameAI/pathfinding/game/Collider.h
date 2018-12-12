#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL_rect.h"
#include <string>

using namespace std;

class Unit;

enum ColliderType
{
	INVALID_COLLIDER_TYPE = -1,
	PLAYER,
	COIN,
	ENEMY,
	POWERUP,
	HEALTH_POWER
};

class Collider
{

private:
	SDL_Rect mCollider;
	ColliderType mTag;

	Unit* mParentObject;

public:
	Collider();
	~Collider();

	void initCollider(int x, int y, int w, int h, ColliderType tag, Unit* parent);

	int getX();
	int getY();
	int getW();
	int getH();

	void setX(int x);
	void setY(int y);
	void setW(int w);
	void setH(int h);

	Unit* getUnit();

	ColliderType getTag();
	void setTag(ColliderType tag);

};

#endif // !COLLIDER_H