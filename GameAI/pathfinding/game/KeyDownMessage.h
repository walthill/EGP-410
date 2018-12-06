#pragma once

#include "GameMessage.h"

class KeyDownMessage :public GameMessage
{
public:
	KeyDownMessage(const int& key);
	~KeyDownMessage();

	void process();
	void initializePlayerPathing(Vector2D pos);
	bool clearPathRaycast(Vector2D fromPos, Vector2D toPos);


private:
	int mKey;
};