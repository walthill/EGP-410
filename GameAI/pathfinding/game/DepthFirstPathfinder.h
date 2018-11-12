#ifndef DEPTH_FIRST_H
#define DEPTH_FIRST_H

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class DepthFirstPathfinder:public GridPathfinder
{
public:
	DepthFirstPathfinder( Graph* pGraph );
	DepthFirstPathfinder();
	~DepthFirstPathfinder();

	Path* findPath( Node* pFrom, Node* pTo );//make sure to delete the path when you are done!

private:
};


#endif

