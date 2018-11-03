#pragma once

#include "GameMessage.h"

class KeyDownMessage :public GameMessage
{
public:
	KeyDownMessage(const int& key);
	~KeyDownMessage();

	void process();

private:
	int mKey;
};