#include "DijkstraPathfinder.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include "MemoryTracker.h"
#include <PerformanceTracker.h>
#include <vector>
#include <algorithm>
#include "PriorityQueue.h"


DijkstraPathfinder::DijkstraPathfinder(Graph* graph)
: GridPathfinder(dynamic_cast<GridGraph*>(graph))
{
	#ifdef VISUALIZE_PATH
	mpPath = NULL;
	#endif
}

DijkstraPathfinder::~DijkstraPathfinder()
{
	#ifdef VISUALIZE_PATH
	delete mpPath;
	#endif
}

Path* DijkstraPathfinder::findPath(Node* fromNode, Node* toNode)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	Path* returnPath = new Path();
	//allocate nodes to open list and place starting node in it
	//list<Node*> openNodes;
	//init struct
	mNodeRecord = {};
	mNodeRecord.node = fromNode;
	mNodeRecord.connection = nullptr;
	mNodeRecord.costSoFar = 0;

	PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare> mOpenList, mClosedList;

	//list<NodeRecord> mClosedList; //TODO: more efficient data structure
	//list<NodeRecord> mOpenList;

	mOpenList.push(mNodeRecord);
//	mOpenList.push_front(mNodeRecord);

	#ifdef VISUALIZE_PATH
	delete mpPath;
	//empty out the closed list
	
//	mClosedList.empty();
	mVisitedNodes.clear();
	//mClosedList.push_back(mNodeRecord);
	//mVisitedNodes.push_back(fromNode);
	#endif



	float endNodeCost;
	Node* endNode;
	NodeRecord currentRecord = {}, endNodeRecord = {};
	//bool toNodeAdded = false;
	
	//float smallestValue = 100000.0f, value;

	while (currentRecord.node != toNode && mOpenList.size() > 0)
	{
		//find smallest element
		
	//	for (auto record = mOpenList.begin(); record != mOpenList.end(); ++record)
		{
			//value = record->costSoFar;

			//if (value <= smallestValue)
			{
				currentRecord = mOpenList.top();
//				currentRecord = mOpenList.front();
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


		/*	for (auto record = mClosedList.begin(); record != mClosedList.end(); ++record) //check if closed list contains the current endNode
			{
				if (record->node == endNode) //skip loop if node is closed
				{
					containedInClosedList = true;
					break;
				}
			}*/

			NodeRecord listCheck = {};
			listCheck.node = endNode;


			PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare>::const_iterator it;

			it = mOpenList.contains(listCheck);

			if (mClosedList.contains(listCheck) != mClosedList.end())
				continue;
			else if (it != mOpenList.end())
			{
				containedInOpenList = false;
				endNodeRecord.insert(it->node, it->connection, it->costSoFar);

				if (endNodeRecord.costSoFar <= endNodeCost)
					continue;
			}
			else
			{
				endNodeRecord = {};
				endNodeRecord.node = endNode;
			}

			endNodeRecord.costSoFar = endNodeCost;
			endNodeRecord.connection = tmpConnection;

			if(!containedInOpenList)
				mOpenList.push(endNodeRecord);//mOpenList.push_back(endNodeRecord);


		//	PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare>::const_iterator it;
			//it = find(mOpenList.begin(), mOpenList.end(), endNode);

			//tmp.node = endNode;

			/*if (mOpenList.find(tmp) != mOpenList.end()) //check if in open list
			{

			}*/
			/*
			{
			tmp = endNode;
		}*/

		/*		NodeRecord tmp = {};
				for (auto record = mOpenList.begin(); record != mOpenList.end(); ++record) //check if closed list contains the current endNode
				{
					if (record->node == endNode) //skip loop if node is closed
					{
						tmp.node = record->node;
						tmp.connection = record->connection;
						tmp.costSoFar = record->costSoFar;

						containedInOpenList = true;
						break;
					}
				}
				*/
				/*	if (containedInClosedList)
						continue;
					else if (containedInOpenList)
					{
						endNodeRecord = listCheck;
						if (endNodeRecord.costSoFar <= endNodeCost)
							continue;
					}
					else //unvisited node, make a record of it
					{
						endNodeRecord = {};
						endNodeRecord.node = endNode;
					}

					endNodeRecord.costSoFar = endNodeCost;
					endNodeRecord.connection = tmpConnection;

					if (!containedInOpenList)
						mOpenList.push(endNodeRecord);//mOpenList.push_back(endNodeRecord);

				}*/

		}
		
		mOpenList.pop();
		//mOpenList.pop_front();
		mClosedList.push(currentRecord);
		mVisitedNodes.push_back(currentRecord.node); //list for visualization
		
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
			PriorityQueue <NodeRecord, vector<NodeRecord>, W_Compare>::const_iterator it;

			it = mClosedList.contains(currentRecord);
			if(it != mClosedList.end())
				currentRecord.connection = it->connection;

/*			for (auto record = mClosedList.begin(); record != mClosedList.end(); ++record) //check if closed list contains the current endNode
			{
				if (record->node == currentRecord.node) //skip loop if node is closed
				{
					currentRecord.connection = record->connection;
					break;
				}
			}*/

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

	/*while (pCurrentNode != toNode && openList.size() > 0)
	{
		//get current node from front of open list
		pCurrentNode = openList.front();
		//remove node from open list
		openList.pop_front();
		//add Node to path
		returnPath->addNode(pCurrentNode);

		//get all the connections for the current node
		vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		//add all toNodes in the connections to the open list, if they are not already in the list
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			Connection* tmpConnection = connections[i];
			Node* tmpToNode = connections[i]->getToNode();
			
			if (!toNodeAdded && !returnPath->containsNode(tmpToNode) &&
				find(openList.begin(), openList.end(), tmpToNode) == openList.end())
			{
				//nodesToVisit.push_front( pTempToNode );//uncomment me for depth-first search //make changeable at runtime?
				openList.push_back(tmpToNode);//uncomment me for breadth-first search

				//if temp node is the goal, stop adding to the open list
				if (tmpToNode == toNode)// && tmpConnection->getCost() < minCost)
				{
					toNodeAdded = true;
				}

				#ifdef VISUALIZE_PATH
				closedList.push_back(tmpToNode);

				//mVisitedNodes.push_back(tmpToNode);
				#endif

			}
		}
	}*/

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	#ifdef VISUALIZE_PATH
	mpPath = returnPath;
	#endif

	return returnPath;

}