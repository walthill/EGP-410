#ifndef NODE_RECORD_H
#define NODE_RECORD_H

#include "GridPathfinder.h"
#include <list>
#include "Node.h"

class Connection;
class Path;
class Graph;
class GraphicsBuffer;
class Grid;

using namespace std;

struct NodeRecord
{
	Node* node;
	Connection* connection;
	float costSoFar;
	float estimatedTotalCost;

	void insert(Node* n, Connection* c, float cost, float estimatedCost = -1.0f) { node = n; connection = c; costSoFar = cost; estimatedTotalCost = estimatedCost; };
	//			void insert(NodeRecord* record) { node = record->node; connection = record->connection; costSoFar = record->costSoFar; };
	
	friend bool operator== (const NodeRecord &lhs, const NodeRecord &rhs) { return  lhs.node == rhs.node; };
	
	bool operator ==(const NodeRecord& rhs) { return node == rhs.node; };
}; // mNodeRecord;


#endif // !NODE_RECORD_H



