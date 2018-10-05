#include <stdio.h>
#include <assert.h>

#include <time.h>
#include <SDL.h>

#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "MouseEvent.h"
#include "EventSystem.h"
#include "Font.h"
#include "GraphicsBufferManager.h"
#include "GameMessageManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "PlayerMoveToMessage.h"
#include "ComponentManager.h"
#include "UnitManager.h"

Game* gpGame = NULL;

const int WIDTH = 1024;
const int HEIGHT = 768;
const Uint32 MAX_UNITS = 100;

Game::Game() 
	:EventListener(nullptr)
	,mpGraphicsSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mpFont(NULL)
	,mShouldExit(false)
	,mBackgroundBufferID("")
	,mpComponentManager(NULL)
	,mpUnitManager(NULL)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	srand(static_cast<unsigned>(time(NULL)));
	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	//create and init GraphicsSystem
	mpGraphicsSystem = new GraphicsSystem();
	bool goodGraphics = mpGraphicsSystem->init( WIDTH, HEIGHT );
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager(mpGraphicsSystem);
	mpSpriteManager = new SpriteManager();

	//init event & input systems
	EventSystem::initInstance(); 
	mpInputSystem = new InputSystem;
	mpInputSystem->initInputSystem();
	installListeners();

	mpComponentManager = new ComponentManager(MAX_UNITS);
	mpUnitManager = new UnitManager(MAX_UNITS);

	//load buffers
	mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID,"wallpaper.bmp");
	mpGraphicsBufferManager->loadBuffer(mPlayerIconBufferID,"arrow.png");
	mpGraphicsBufferManager->loadBuffer(mEnemyIconBufferID,"enemy-arrow.png");
	mpGraphicsBufferManager->loadBuffer(mTargetBufferID,"target.png");

	//load Font
	mpFont = new Font("cour.ttf", 24);
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer( mPlayerIconBufferID );
	Sprite* pArrowSprite = NULL;
	if( pPlayerBuffer != NULL )
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, (float)pPlayerBuffer->getWidth(), (float)pPlayerBuffer->getHeight() );
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer(mEnemyIconBufferID);
	Sprite* pEnemyArrow = NULL;
	if (pAIBuffer != NULL)
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, (float)pAIBuffer->getWidth(), (float)pAIBuffer->getHeight());
	}

	GraphicsBuffer* pTargetBuffer = mpGraphicsBufferManager->getBuffer(mTargetBufferID);
	if (pTargetBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(TARGET_SPRITE_ID, pTargetBuffer, 0, 0, (float)pTargetBuffer->getWidth(), (float)pTargetBuffer->getHeight());
	}

	//setup units
	/*Unit* pUnit = mpUnitManager->createPlayerUnit(*pArrowSprite);
	pUnit->setShowTarget(true);
	pUnit->setSteering(Steering::ARRIVE_FACE, ZERO_VECTOR2D);
	*/
	//create 2 enemies
/*	pUnit = mpUnitManager->createUnit(*pEnemyArrow, true, PositionData(Vector2D((float)gpGame->getGraphicsSystem()->getWidth()-1, 0.0f), 0.0f));
	pUnit->setShowTarget(true);
	pUnit->setSteering(Steering::ARRIVE, ZERO_VECTOR2D, PLAYER_UNIT_ID);*/
	
/*	pUnit = mpUnitManager->createUnit(*pEnemyArrow, true, PositionData(Vector2D(0.0f, (float)gpGame->getGraphicsSystem()->getHeight()-1), 0.0f));
	pUnit->setShowTarget(false);
	pUnit->setSteering(Steering::WANDER, ZERO_VECTOR2D, PLAYER_UNIT_ID);
	*/

	return true;
}

void Game::installListeners()
{
	EventSystem::getInstance()->addListener(QUIT, this);
	EventSystem::getInstance()->addListener(SPAWN, this);
	EventSystem::getInstance()->addListener(MOVE_PLAYER, this);
	EventSystem::getInstance()->addListener(DELETE_UNIT, this);
	EventSystem::getInstance()->addListener(MOUSE_MOTION, this);
}

void Game::cleanup()
{
	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	delete mpFont;
	mpFont = NULL;

	//delete the graphics system
	delete mpGraphicsSystem;
	mpGraphicsSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpComponentManager;
	mpComponentManager = NULL;
	delete mpInputSystem;
	mpInputSystem = NULL;
	EventSystem::cleanupInstance();
}

void Game::beginLoop()
{
	mpLoopTimer->start();
}

const float TARGET_ELAPSED_MS = LOOP_TARGET_TIME / 1000.0f;
	
void Game::processLoop()
{
	mpUnitManager->updateAll(TARGET_ELAPSED_MS);
	mpComponentManager->update(TARGET_ELAPSED_MS);
	
	//draw background
	Sprite* pBackgroundSprite = mpSpriteManager->getSprite( BACKGROUND_SPRITE_ID );
	GraphicsBuffer* pDest = mpGraphicsSystem->getBackBuffer();
	mpGraphicsSystem->draw(*pDest, *pBackgroundSprite, 0.0f, 0.0f);

	//draw units
	mpUnitManager->drawAll();

	//write text at mouse position
	mpGraphicsSystem->writeText(*mpFont, (float)mouseX, (float)mouseY, mouseText, BLACK_COLOR);

	//test of fill region - the red box
	//mpGraphicsSystem->fillRegion(*pDest, Vector2D(300, 300), Vector2D(500, 500), RED_COLOR);
	mpGraphicsSystem->swap();

	mpInputSystem->update(TARGET_ELAPSED_MS);

}

bool Game::endLoop()
{
	//mpMasterTimer->start();
	mpLoopTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}

void Game::handleEvent(const Event& theEvent)
{
	mEventType = theEvent.getType();

	switch (mEventType)
	{
		case MOUSE_MOTION:
		{
			const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);
			//create mouse text
			std::stringstream mousePos;
			mouseX = mouseEvent.getX();
			mouseY = mouseEvent.getY();
			mouseText = to_string(mouseX) + ":" + to_string(mouseY);
			break;
		}
		case QUIT:
			mShouldExit = true;
			break;
		case SPAWN:
		{
			for (int i = 0; i < 10; i++)
			{
				Unit * pPlayer = gpGame->getUnitManager()->getPlayerUnit();
				mpUnitManager->createRandomUnit(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID));
			}
			break;
		}
		case DELETE_UNIT:
			mpUnitManager->deleteRandomUnit();
			break;
		case MOVE_PLAYER:
		{	
			/*const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);
			Unit* pPlayer = gpGame->getUnitManager()->getPlayerUnit();
			Vector2D pos(mouseEvent.getX(), mouseEvent.getY());
			pPlayer->setSteering(Steering::ARRIVE_FACE, pos);
			*/break;
		}
	}
}