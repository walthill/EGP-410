#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Unit;

class PathToMessage:public GameMessage
{
public:
	PathToMessage(Unit* owner, const Vector2D& from, const Vector2D& to );
	~PathToMessage();

	const Vector2D& getFrom() const { return mFrom; };
	const Vector2D& getTo() const { return mTo; };

	void process();

private:
	Unit* mOwner;
	Vector2D mFrom;
	Vector2D mTo;
};