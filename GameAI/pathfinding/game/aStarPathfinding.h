#ifndef A_STAR_H
#define A_STAR_H

#include "GameApp.h"
#include "GridPathfinder.h"
#include <list>
#include <Vector2D.h>
#include "Node.h"
#include "NodeRecord.h"
#include "Grid.h"

class Connection;
class Path;
class Graph;
class GraphicsBuffer;
//class Grid;

using namespace std;

class aStarPathfinder : public GridPathfinder
{
	private:
		
		struct PathHeuristic
		{
			Node* goalNode;
			Vector2D goalPos;

			void setGoal(Node* goal) 
			{ 
				goalNode = goal;
				GameApp * pGame = dynamic_cast<GameApp*>(gpGame);
				goalPos = pGame->getGrid()->getULCornerOfSquare(goalNode->getId());
			};
			
			float estimate(Node* node) 
			{ 
				Vector2D nodePos;
				GameApp * pGame = dynamic_cast<GameApp*>(gpGame);
				nodePos = pGame->getGrid()->getULCornerOfSquare(node->getId());
		
/*				float val;  
				
				if (goalNode->getId() >= node->getId())
					val = goalNode->getId() - node->getId();
				else
					val = goalNode->getId();
					*/
		//		if (val < 0)
			//		cout << "poop";
				return (goalPos - nodePos).getLength(); 
			}; //euclidean distance - underestimates
		} mHeuristic;


		NodeRecord mNodeRecord;

	public:
		aStarPathfinder(Graph* graph);
		~aStarPathfinder();

		Path* findPath(Node* fromNode, Node* toNode);
};

#endif // !A_STAR_H
