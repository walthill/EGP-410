#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "DebugContent.h"

class GridPathfinder;

class ScoreboardContent : public DebugContent
{
public:
	ScoreboardContent();
	~ScoreboardContent() {};

	std::string getDebugString();

	void setScoreDisplay(int score) { mScore = score; };
	void setTimeDisplay(int min, int sec) { mMin = min; mSec = sec; };
	void setTextDisplay(std::string str) { mText = str; };
	void showLoseText() { mText = mLoseText; };

	void addFlavorText(std::string text) { mFlavorText = text; };
	void addLoseText(std::string text) { mLoseText = text; };

private:
	int mScore;
	int mMin = 0, mSec = 0;

	std::string mLoseText, mFlavorText, mText;
};

#endif // !SCOREBOARD_H

