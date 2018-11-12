#ifndef A_STAR_H
#define A_STAR_H

#include "GameApp.h"
#include "GridPathfinder.h"
#include <list>
#include <Vector2D.h>
#include "Node.h"
#include "NodeRecord.h"
#include "Grid.h"
#include "PathSmooth.h"

class Connection;
class Path;
class Graph;
class GraphicsBuffer;

using namespace std;

class AStarPathfinder : public GridPathfinder
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

				return (goalPos - nodePos).getLength(); 
			}; //euclidean distance - underestimates
		} mHeuristic;


		NodeRecord mNodeRecord;

	public:
		AStarPathfinder(Graph* graph);
		AStarPathfinder();
		~AStarPathfinder();

		Path* findPath(Node* fromNode, Node* toNode);
};

#endif // !A_STAR_H
