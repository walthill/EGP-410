#ifndef A_STAR_H
#define A_STAR_H

#include "GridPathfinder.h"
#include <list>
#include "Node.h"
#include "NodeRecord.h"

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


		NodeRecord mNodeRecord;

	public:
		aStarPathfinder(Graph* graph);
		~aStarPathfinder();

		Path* findPath(Node* fromNode, Node* toNode);
};

#endif // !A_STAR_H
