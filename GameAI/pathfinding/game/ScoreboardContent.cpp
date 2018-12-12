#include "ScoreboardContent.h"
#include "GridPathfinder.h"
#include <sstream>

using namespace std;

ScoreboardContent::ScoreboardContent()
{
}

string ScoreboardContent::getDebugString()
{
	stringstream theStream;

	theStream << "   Net Worth : $" << mScore;

	if(mSec < 10)
		theStream << "   Time:" << mMin << ":0" << mSec;
	else
		theStream << "   Time:" << mMin << ":" << mSec;
	
	theStream << "                " << mText;

	return theStream.str();
}

