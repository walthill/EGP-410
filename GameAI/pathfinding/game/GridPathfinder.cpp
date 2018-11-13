#include "GridPathfinder.h"
#include "GridGraph.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "Game.h"
#include "GameApp.h"
#include "GraphicsBuffer.h"
#include "Color.h"
#include <cassert>
#include <iostream>

using namespace std;

GridPathfinder::GridPathfinder( GridGraph* pGraph )
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
	mpPath = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

float lerp(int value, int start, int end)
{
	//returns float representing how far value is between start and end
	assert(start <= end);

	float lerpVal = 0.0f;

	if (start <= end)
	{
		int range = end - start;
		lerpVal = value / (float)range;
	}
	return lerpVal;
}


#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization(Grid* pGrid, GraphicsBuffer* pDest)
{
	//cout << "mpPath:" << mpPath << endl;

	delete mpVisualizer;

	GameApp* gpGameApp = dynamic_cast<GameApp*>(gpGame);

	
	/*if (gpGameApp->gpPaths.size() != 0)
	{
		delete mpPath;
		mpPath = gpGameApp->gpPaths[0];
		gpGameApp->gpPaths.erase(gpGameApp->gpPaths.begin());
	}*/
	
	
	mpVisualizer = new GridVisualizer(pGrid);
	

	for (int i = 0; i < gpGameApp->gpPaths.size(); i++)
	{
		//set mpPath to the next path to be visualized
		mpPath = gpGameApp->gpPaths[i];

		static Color pathColor = Color(255, 64, 64);
		static Color visitedColor = GREEN_COLOR;
		static Color startColor = Color(1, 255, 128); //green
		static Color stopColor = Color(1, 128, 255); //blue


		if (mpPath != NULL && mpPath->getNumNodes() > 0)
		{

			Color currentPathColor = pathColor;
			unsigned int numNodes = mpPath->getNumNodes();

			for (unsigned int i = 1; i < numNodes - 1; i++)
			{
				mpVisualizer->addColor(mpPath->peekNode(i)->getId(), currentPathColor);
				float lerpVal = lerp(i, 0, numNodes);
				currentPathColor = Color((int)(255 * (1.0f - lerpVal)), currentPathColor.getG(), currentPathColor.getB());
			}


			//add beginning and ending color
			mpVisualizer->addColor(mpPath->peekNode(0)->getId(), startColor);
			mpVisualizer->addColor(mpPath->peekNode(mpPath->getNumNodes() - 1)->getId(), stopColor);

		}

	}
	mpPath = NULL;
	mpVisualizer->draw(*pDest);
}
#endif