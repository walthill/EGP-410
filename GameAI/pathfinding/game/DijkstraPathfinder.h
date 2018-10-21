#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "GridPathfinder.h"
#include "NodeRecord.h"
#include <list>

class Connection;
class Node;
class Path;
class Graph;
class GraphicsBuffer;
class Grid;

using namespace std;

class DijkstraPathfinder : public GridPathfinder
{
	private:
		NodeRecord mNodeRecord;
		
	public:
		DijkstraPathfinder(Graph* graph);
		~DijkstraPathfinder();

		Path* findPath(Node* fromNode, Node* toNode);
};

#endif // !DIJKSTRA_H
