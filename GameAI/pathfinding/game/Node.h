#pragma once

#include <Trackable.h>

const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node:public Trackable
{
public:
	Node( const NODE_ID& id );
	Node();
	~Node();

	const NODE_ID& getId() const {return mId;};
	friend bool operator== (const Node &lhs, const Node &rhs) { return  lhs.mId== rhs.mId; };

private:
	const NODE_ID mId;
};