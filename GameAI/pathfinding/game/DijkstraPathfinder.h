#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "GridPathfinder.h"
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
		struct NodeRecord
		{
			Node* node;
			Connection* connection;
			float costSoFar;

			void insert(Node* n, Connection* c, float cost) { node = n; connection = c; costSoFar = cost; };
			void insert(NodeRecord* record) { node = record->node; connection = record->connection; costSoFar = record->costSoFar; };
		} mNodeRecord;

		
	public:
		DijkstraPathfinder(Graph* graph);
		~DijkstraPathfinder();

		Path* findPath(Node* fromNode, Node* toNode);
};

#endif // !DIJKSTRA_H
