#include "InputSystem.h"
#include "SDL.h"


InputSystem::InputSystem() : mKeyEvent()
{
}


InputSystem::~InputSystem()
{
	cleanupInputSystem();
}


void InputSystem::cleanupInputSystem()
{
}


bool InputSystem::initInputSystem()
{
	//controller help from LazyFoo @ http://lazyfoo.net/tutorials/SDL/19_gamepads_and_joysticks/index.php
	//Check for joysticks
	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No joysticks connected!\n");
	}
	else
	{
		//Load joystick
		mGameController = SDL_JoystickOpen(0);
		if (mGameController == NULL)
		{
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
	}

	cout << "Initialized InputSystem" << endl;

	return true;
}


void InputSystem::update(double elapsedTime)
{	
	getInputEvents();
}


void InputSystem::getInputEvents()
{

	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
		case SDL_MOUSEMOTION:
		//	EventSystem::getInstance()->fireEvent(MouseEvent(MOUSE_MOTION, mEvent.motion.x, mEvent.motion.y));
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mEvent.button.button == SDL_BUTTON_LEFT)
			{
				mKeyEvent.setType(SET_PATH);
				EventSystem::getInstance()->fireEvent(MouseEvent(SET_PATH, mEvent.motion.x, mEvent.motion.y));
			}
			break;
		case SDL_KEYDOWN:
			if (mEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				mKeyEvent.setType(QUIT);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_f)
			{
				cout << "InputSystem: F" << endl;
				mKeyEvent.setType(DEPTH_FIRST);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_d)
			{
				cout << "InputSystem: D" << endl;
				mKeyEvent.setType(DIJKSTRA);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_a)
			{
				cout << "InputSystem: A" << endl;
				mKeyEvent.setType(ASTAR);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			break;
		case SDL_KEYUP:
			if (mEvent.key.keysym.sym == SDLK_w)
			{
				//cout << "InputSystem: Up arrow" << endl;
			//	mKeyEvent.setType(UP_ARROW_RELEASED);
			//	EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_s)
			{
				//cout << "InputSystem: Down arrow" << endl;
			//	mKeyEvent.setType(DOWN_ARROW_RELEASED);
			//	EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_a)
			{
				//cout << "InputSystem: Left arrow" << endl;
		//		mKeyEvent.setType(LEFT_ARROW_RELEASED);
		//		EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_d)
			{
				//cout << "InputSystem: Right arrow" << endl;
		//		mKeyEvent.setType(RIGHT_ARROW_RELEASED);
		//		EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			break;
		case SDL_JOYBUTTONDOWN:  /* Handle Joystick Button Presses */
			/*if (mEvent.jbutton.button == 0)
			{
				//cout << "InputSystem: Space" << endl;
				mKeyEvent.setType(ENTER);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.jbutton.button == 7)
			{
				//cout << "InputSystem: ESC" << endl;
				mKeyEvent.setType(ESC);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}*/
			break;
		case SDL_JOYAXISMOTION:
			/*if (mEvent.jaxis.which == 0)
			{
				//right stick x-axis motion
				if (mEvent.jaxis.axis == 0)
				{
					if (mEvent.jaxis.value < -mLeftStickXDeadZone)
					{
						//a
					//	cout << "InputSystem: Left arrow" << endl;
						mKeyEvent.setType(LEFT_ARROW_CONTROLLER);
						EventSystem::getInstance()->fireEvent(mKeyEvent);
					}
					else if (mEvent.jaxis.value > mLeftStickXDeadZone)
					{
						//d
					//	cout << "InputSystem: Right arrow" << endl;
						mKeyEvent.setType(RIGHT_ARROW_CONTROLLER);
						EventSystem::getInstance()->fireEvent(mKeyEvent);
					}
					else
					{
					//	cout << "InputSystem: Left arrow" << endl;
						mKeyEvent.setType(LEFT_ARROW_RELEASED_CONTROLLER);
						EventSystem::getInstance()->fireEvent(mKeyEvent);

					//	cout << "InputSystem: Right arrow" << endl;
						mKeyEvent.setType(RIGHT_ARROW_RELEASED_CONTROLLER);
						EventSystem::getInstance()->fireEvent(mKeyEvent);
					}
				}
				//left stick y-axis motion
				if (mEvent.jaxis.axis == 1)
				{
					if (mEvent.jaxis.value < -mLeftStickYDeadZone)
					{
						//w
					//	cout << "InputSystem: Up arrow" << endl;
						mKeyEvent.setType(UP_ARROW_CONTROLLER);
						EventSystem::getInstance()->fireEvent(mKeyEvent);
					}
					else if (mEvent.jaxis.value > mLeftStickYDeadZone)
					{
						//s
					//	cout << "InputSystem: Down arrow" << endl;
						mKeyEvent.setType(DOWN_ARROW_CONTROLLER);
						EventSystem::getInstance()->fireEvent(mKeyEvent);
					}
					else
					{
					//	cout << "InputSystem: Up arrow" << endl;
						mKeyEvent.setType(UP_ARROW_RELEASED_CONTROLLER);
						EventSystem::getInstance()->fireEvent(mKeyEvent);

					//	cout << "InputSystem: Down arrow" << endl;
						mKeyEvent.setType(DOWN_ARROW_RELEASED_CONTROLLER);
						EventSystem::getInstance()->fireEvent(mKeyEvent);
					}
				}
				if (mEvent.jaxis.axis == 3) //right stick x
				{
					xAxis = SDL_JoystickGetAxis(mGameController, mEvent.jaxis.axis);
					yAxis = SDL_JoystickGetAxis(mGameController, 4);//RS y axis

					if (mEvent.jaxis.value < -mRightStickXDeadZone || mEvent.jaxis.value > mRightStickXDeadZone)
					{
					//	cout << "InputSystem: X" << endl;
						EventSystem::getInstance()->fireEvent(MouseEvent(MOUSE_MOTION, xAxis,yAxis));
					}
					
					break;
				}
				if (mEvent.jaxis.axis == 4) //right stick y
				{
					xAxis = SDL_JoystickGetAxis(mGameController, 3);
					yAxis = SDL_JoystickGetAxis(mGameController, mEvent.jaxis.axis);
					if (mEvent.jaxis.value < -mRightStickYDeadZone || mEvent.jaxis.value > mRightStickYDeadZone)
					{
					//	cout << "InputSystem: Y" << endl;
						EventSystem::getInstance()->fireEvent(MouseEvent(MOUSE_MOTION, xAxis, yAxis));
					}
				}
				if (mEvent.jaxis.axis == 5) //right trigger shoot
				{
					//fire on RT press
					if (mEvent.jaxis.value > 32700)
					{
						mKeyEvent.setType(LEFT_MOUSE_DOWN);
						EventSystem::getInstance()->fireEvent(mKeyEvent);
						cout << xAxis<< endl;
					}
				}
			}*/
			break;

		case SDL_JOYDEVICEADDED:
		case SDL_JOYDEVICEREMOVED:
			cout << "InputSystem: Device (dis)connect" << endl;
			mKeyEvent.setType(DEVICE_ADDED_OR_REMOVED);
			EventSystem::getInstance()->fireEvent(mKeyEvent);
			break;
		}
	};
}