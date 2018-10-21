#include "aStarPathfinding.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "MemoryTracker.h"
#include <PerformanceTracker.h>
#include <vector>
#include <algorithm>


aStarPathfinder::aStarPathfinder(Graph* graph)
	: GridPathfinder(dynamic_cast<GridGraph*>(graph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif
}

aStarPathfinder::~aStarPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path* aStarPathfinder::findPath(Node* fromNode, Node* toNode)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	Path* returnPath = new Path();
	float endNodeHeurisitc;
	mHeuristic.setGoal(toNode);

	//allocate nodes to open list and place starting node in it
	//list<Node*> openNodes;
	//init struct
	mNodeRecord = {};
	mNodeRecord.node = fromNode;
	mNodeRecord.connection = nullptr;
	mNodeRecord.costSoFar = 0;
	mNodeRecord.estimatedTotalCost = mHeuristic.estimate(fromNode);

	list<NodeRecord> mClosedList; //TODO: more efficient data structure
	list<NodeRecord> mOpenList;
	
	mOpenList.push_front(mNodeRecord);

#ifdef VISUALIZE_PATH
	delete mpPath;
	//empty out the closed list

	mClosedList.clear();
	mVisitedNodes.clear();
	//mClosedList.push_back(mNodeRecord);
	//mVisitedNodes.push_back(fromNode);
#endif


	bool shouldDoubleBack = false;
	float endNodeCost;
	Node* endNode;
	NodeRecord currentRecord = {}, endNodeRecord = {};
	//bool toNodeAdded = false;

	float smallestValue = 100000.0f, value;

	while (currentRecord.node != toNode && mOpenList.size() > 0)
	{
		//find element with smallest estimated total cost
		for (auto record = mOpenList.begin(); record != mOpenList.end(); ++record)
		{
			float val = record->estimatedTotalCost;
			
			if (val <= smallestValue)
			{
				shouldDoubleBack = false;
				currentRecord.insert(record->node, record->connection, record->costSoFar, record->estimatedTotalCost);
				//returnPath->addNode(currentRecord.node); //display surveyed route
				smallestValue = val;
				break;
			}
			else
			{
				shouldDoubleBack = true; //handle obstacle dead ends
			}
		}
		
		if (shouldDoubleBack)
		{
			currentRecord = mOpenList.back();
			smallestValue = currentRecord.estimatedTotalCost;
		}
		//	for (auto record = mOpenList.begin(); record != mOpenList.end(); ++record)
		{
			//value = record->costSoFar;

			//if (value <= smallestValue)
			{
			//	currentRecord = mOpenList.front();
				//smallestValue = value;
			
			}
		}
	
		if (currentRecord.node == toNode)
			break;

		vector<Connection*> connections = mpGraph->getConnections(currentRecord.node->getId());

		for (unsigned int i = 0; i < connections.size(); i++)
		{
			bool containedInClosedList = false, containedInOpenList = false;
			Connection* tmpConnection = connections[i];

			endNode = tmpConnection->getToNode();
			endNodeCost = currentRecord.costSoFar + connections.at(i)->getCost();


			NodeRecord tmpClosed = {};
 			for (auto record = mClosedList.begin(); record != mClosedList.end(); ++record) //check if closed list contains the current endNode
			{
				if (record->node == endNode) //skip loop if node is closed
				{
					tmpClosed.node = record->node;
					tmpClosed.connection = record->connection;
					tmpClosed.costSoFar = record->costSoFar;
					tmpClosed.estimatedTotalCost = record->estimatedTotalCost;
					containedInClosedList = true;
					break;
				}
			}

			NodeRecord tmpOpen = {};
			for (auto record = mOpenList.begin(); record != mOpenList.end(); ++record) //check if closed list contains the current endNode
			{
				if (record->node == endNode) //skip loop if node is closed
				{
					tmpOpen.node = record->node;
					tmpOpen.connection = record->connection;
					tmpOpen.costSoFar = record->costSoFar;
					tmpOpen.estimatedTotalCost = record->estimatedTotalCost;

					containedInOpenList = true;
					break;
				}
			}

			if (containedInClosedList)
			{
				endNodeRecord = tmpClosed;

				if (endNodeRecord.costSoFar <= endNodeCost)
					continue;

				//remove from closed list
				NodeRecord toDelete;
				for (auto record = mClosedList.begin(); record != mClosedList.end(); ++record) 
				{
					if (record->node == endNodeRecord.node)
					{
						toDelete = endNodeRecord;
					}
				}

				if(toDelete.node != nullptr)
					mClosedList.remove(toDelete);

				endNodeHeurisitc = endNodeRecord.estimatedTotalCost - endNodeRecord.costSoFar;
			}
			else if (containedInOpenList)
			{
				endNodeRecord = tmpOpen;
				if (endNodeRecord.costSoFar <= endNodeCost)
					continue;

				endNodeHeurisitc = endNodeRecord.connection->getCost() - endNodeRecord.costSoFar;
			}
			else //unvisited node, make a record of it
			{
				endNodeRecord = {};
				endNodeRecord.node = endNode;
				endNodeHeurisitc = mHeuristic.estimate(endNode); //not toNode?
			}

			endNodeRecord.costSoFar = endNodeCost;
			endNodeRecord.connection = tmpConnection;
			endNodeRecord.estimatedTotalCost = endNodeCost + endNodeHeurisitc;

			if (!containedInOpenList)
				mOpenList.push_back(endNodeRecord);

		}


//		if(mOpenList.size() == 1)
	//		mOpenList.pop_front();
		
		{
			NodeRecord toDelete;
			for (auto record = mOpenList.begin(); record != mOpenList.end(); ++record) //check if closed list contains the current endNode
			{
				if (record->node == currentRecord.node)
				{
					toDelete = currentRecord;
					break;
					//mOpenList
				}
			}
			mOpenList.remove(toDelete);
		}

		mClosedList.push_back(currentRecord);
		mVisitedNodes.push_back(currentRecord.node);

	}

	if (currentRecord.node != toNode)
		return NULL;
	else
	{
		//create Path
		Path* path = new Path();

		while (currentRecord.node != fromNode)
		{
			path->addNode(currentRecord.node);

			currentRecord.node = currentRecord.connection->getFromNode();

			//find next connection in the closed list
			/*list<NodeRecord>::iterator it;
			it = find(mClosedList.begin(), mClosedList.end(), currentRecord);
			if ( it != mClosedList.end())
				currentRecord.connection = it->connection;*/
				

			for (auto record = mClosedList.begin(); record != mClosedList.end(); ++record) //check if closed list contains the current endNode
			{
				if (record->node == currentRecord.node) //skip loop if node is closed
				{
					currentRecord.connection = record->connection;
					break;
				}
			}

			//currentRecord.connection = mClosedList.back().connection; //TODO: get the proper connection here
			//mClosedList.pop_back();
			//currentRecord.connection = currentRecord.connection;
			//	currentRecord.costSoFar = currentRecord.costSoFar;
		}
		int size = path->getNumNodes();
		for (int i = 0; i < size; i++)
		{
			returnPath->addNode(path->getAndRemoveNextNode());
		}

		delete path;
	}

	
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mpPath = returnPath;
#endif

	return returnPath;

}