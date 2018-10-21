#ifndef A_STAR_H
#define A_STAR_H

#include "GridPathfinder.h"
#include <list>
#include <assert.h>
#include "Node.h"

class Connection;
//class Node;
class Path;
class Graph;
class GraphicsBuffer;
class Grid;

using namespace std;

class aStarPathfinder : public GridPathfinder
{
	private:
		struct NodeRecord
		{
			Node* node;
			Connection* connection;
			float costSoFar;
			float estimatedTotalCost;

			void insert(Node* n, Connection* c, float cost, float estimatedCost) { node = n; connection = c; costSoFar = cost; estimatedTotalCost = estimatedCost; };
//			void insert(NodeRecord* record) { node = record->node; connection = record->connection; costSoFar = record->costSoFar; };
			bool operator ==(const NodeRecord& rhs) { return node == rhs.node; };
		} mNodeRecord;

		struct PathHeuristic
		{
			Node* goalNode;

			void setGoal(Node* goal) { goalNode = goal; };
			float estimate(Node* node) 
			{ 
				float val;  
				if (goalNode->getId() >= node->getId())
					val = goalNode->getId() - node->getId();
				else
					val = goalNode->getId();

		//		if (val < 0)
			//		cout << "poop";
				return val; 
			}; //euclidean distance - underestimates
		} mHeuristic;

	public:
		aStarPathfinder(Graph* graph);
		~aStarPathfinder();

		Path* findPath(Node* fromNode, Node* toNode);
};

#endif // !A_STAR_H
