#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "GridPathfinder.h"

class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DijkstraPathfinder : public GridPathfinder
{
	private:
	public:
		DijkstraPathfinder(Graph* graph);
		~DijkstraPathfinder();

		Path* findPath(Node* fromNode, Node* toNode);
};

#endif // !DIJKSTRA_H
