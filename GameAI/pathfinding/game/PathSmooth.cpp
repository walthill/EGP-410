#include "PathSmooth.h"
#include "Path.h"
#include "GridGraph.h"
#include "Grid.h"
#include "GameApp.h"
#include "Node.h"


PathSmooth::PathSmooth()
{
}

PathSmooth::~PathSmooth()
{
}

Path* PathSmooth::smoothPath(Path* pathToSmooth)
{
	Path* mPathToFollow = new Path();
	int smoothingIndex = 2;
	int destinationNodeIndex = pathToSmooth->getNumNodes() - 1;
	int outPathEndIndex;

	//no need to smooth if path is only 2 nodes
	if (pathToSmooth->getNumNodes() == mNO_NEED_TO_SMOOTH) 
		return pathToSmooth;

	mPathToFollow->addNode(pathToSmooth->peekNode(0));

	while (smoothingIndex < pathToSmooth->getNumNodes() -1)
	{
		outPathEndIndex = mPathToFollow->getNumNodes() - 1;

		//check for blocking tile, if one is found back up and set a smoothing path node
		bool clearPath = clearPathRaycast(mPathToFollow->peekNode(outPathEndIndex), pathToSmooth->peekNode(smoothingIndex));
		
		if (!clearPath)
			mPathToFollow->addNode(pathToSmooth->peekNode(smoothingIndex - 1));

		smoothingIndex++;
	}

	//get destination node and add to ouput
	mPathToFollow->addNode(pathToSmooth->peekNode(destinationNodeIndex));

	delete pathToSmooth;
	return mPathToFollow;

}

bool PathSmooth::clearPathRaycast(Node* startCastNode, Node* nextNode)
{
	GameApp* pGameApp = dynamic_cast<GameApp*>(gpGame);
	
	Vector2D direction, toPos, fromPos;
	bool result = true;

	fromPos = pGameApp->getGrid()->getULCornerOfSquare(startCastNode->getId());
	toPos = pGameApp->getGrid()->getULCornerOfSquare(nextNode->getId());
	
	direction = toPos - fromPos;

	float posX = fromPos.getX();
	float posY = fromPos.getY();

	for (size_t i = 0; i < mRAY_ITERATORS; i++)
	{
		bool pathBlocked = pGameApp->getGrid()->getValueAtPixelXY((int)posX, (int)posY) == BLOCKING_VALUE;

		if (pathBlocked)
		{
			result = false;
			break;
		}

		//shoot raycast
		posX = posX + (direction.getX() / mRAY_ITERATORS);
		posY = posY + (direction.getY() / mRAY_ITERATORS);
	}

	return result;
}
