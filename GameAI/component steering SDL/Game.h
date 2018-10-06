#pragma once

#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Defines.h"
#include "EventListener.h"
#include "InputSystem.h"
#include <string>
#include <sstream>

class GraphicsSystem;
class GraphicsBuffer;
class Font;
class GraphicsBufferManager;
class SpriteManager;
class KinematicUnit;
class Timer;
class ComponentManager;
class Unit;
class UnitManager;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType TARGET_SPRITE_ID = 3;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame

class Game: public EventListener
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void beginLoop();
	void processLoop();
	bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	//inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline ComponentManager* getComponentManager() { return mpComponentManager; };
	inline UnitManager* getUnitManager() { return mpUnitManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline void handleEvent(const Event& theEvent);
	inline void installListeners();
	
	void loadGameData();
	void saveGameData();
	
	bool checkRadiusChange();
	void setRadiusChange(bool radiusChanged);
	bool checkWeightChange();
	void setWeightChange(bool weightChanged);

	struct FlockData
	{
		float wanderWeight, seaparationWeight, groupAlignWeight, cohesionWeight;
		float separationRadius, cohesionRadius, groupAlignRadius;
	} mFlockData;
	
	FlockData getFlockData() const { return mFlockData; };


private:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	
	InputSystem* mpInputSystem;
	EventType mEventType;
	int mouseX, mouseY;//used in input system
	string mouseText; //display mouse pos

	SpriteManager* mpSpriteManager;
//	GameMessageManager* mpMessageManager;
	ComponentManager* mpComponentManager;
	UnitManager* mpUnitManager;
	Font* mpFont;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	bool mShouldExit;

	//should be somewhere else
	GraphicsBufferID mBackgroundBufferID = "woods";
	GraphicsBufferID mPlayerIconBufferID = "player";
	GraphicsBufferID mEnemyIconBufferID = "enemy";
	GraphicsBufferID mTargetBufferID = "target";

	const string mINI_FILE = "data.ini";
	const float mWEIGHT_CHANGE_VALUE = 0.1f;
	const float mRADIUS_CHANGE_VALUE = 10.0f;
	bool mDoWeightChange = false, mDoRadiusChange = false;
};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

