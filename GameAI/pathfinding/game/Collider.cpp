#include "Collider.h"
#include "component steering/Unit.h"

Collider::Collider()
{
	mCollider.x = 0;
	mCollider.y = 0;
	mCollider.h = 0;
	mCollider.w = 0;
}

Collider::~Collider()
{

}

void Collider::initCollider(int x, int y, int w, int h, ColliderType tag, Unit* parent)
{
	mCollider.x = x;
	mCollider.y = y;
	mCollider.h = w;
	mCollider.w = h;

	mTag = tag;

	mParentObject = parent;
}

int Collider::getX()
{
	return mCollider.x;
}

int Collider::getY()
{
	return mCollider.y;
}

int Collider::getW()
{
	return mCollider.w;
}

int Collider::getH()
{
	return mCollider.h;
}


void Collider::setX(int x)
{
	mCollider.x = x;
}
void Collider::setY(int y)
{
	mCollider.y = y;
}
void Collider::setW(int w)
{
	mCollider.w = w;
}

void Collider::setH(int h)
{
	mCollider.h = h;
}


Unit* Collider::getUnit()
{
	return mParentObject;
}

ColliderType Collider::getTag()
{
	return mTag;
}

void Collider::setTag(ColliderType tag)
{
	mTag = tag;
}