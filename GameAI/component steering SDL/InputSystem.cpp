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
			EventSystem::getInstance()->fireEvent(MouseEvent(MOUSE_MOTION, mEvent.motion.x, mEvent.motion.y));
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mEvent.button.button == SDL_BUTTON_LEFT)
			{
				mKeyEvent.setType(MOVE_PLAYER);
				EventSystem::getInstance()->fireEvent(MouseEvent(MOVE_PLAYER, mEvent.motion.x, mEvent.motion.y));
			}
			break;
		case SDL_KEYDOWN:
			if (mEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				//cout << "InputSystem: ESC" << endl;
				mKeyEvent.setType(QUIT);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_RETURN)
			{
				cout << "InputSystem: ENTER" << endl;
				mKeyEvent.setType(SPAWN);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_1)
			{
				cout << "InputSystem: 1" << endl;
				mKeyEvent.setType(WANDER_UP);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_2)
			{
				cout << "InputSystem: 2" << endl;
				mKeyEvent.setType(WANDER_DOWN);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_3)
			{
				cout << "InputSystem: 3" << endl;
				mKeyEvent.setType(GROUP_ALIGN_UP);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_4)
			{
				cout << "InputSystem: 4" << endl;
				mKeyEvent.setType(GROUP_ALIGN_DOWN);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_5)
			{
				cout << "InputSystem: 5" << endl;
				mKeyEvent.setType(COHESION_UP);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_6)
			{
				cout << "InputSystem: 6" << endl;
				mKeyEvent.setType(COHESION_DOWN);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_7)
			{
				cout << "InputSystem: 7" << endl;
				mKeyEvent.setType(SEPARATION_UP);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_8)
			{
				cout << "InputSystem: 8" << endl;
				mKeyEvent.setType(SEPARATION_DOWN);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_q)
			{
				cout << "InputSystem: q" << endl;
				mKeyEvent.setType(SEP_RADIUS_UP);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_w)
			{
				cout << "InputSystem: w" << endl;
				mKeyEvent.setType(SEP_RADIUS_DOWN);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_e)
			{
				cout << "InputSystem: e" << endl;
				mKeyEvent.setType(GROUP_RADIUS_UP);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_r)
			{
				cout << "InputSystem: r" << endl;
				mKeyEvent.setType(GROUP_RADIUS_DOWN);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_t)
			{
				cout << "InputSystem: t" << endl;
				mKeyEvent.setType(COH_RADIUS_UP);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}

			if (mEvent.key.keysym.sym == SDLK_y)
			{
				cout << "InputSystem: y" << endl;
				mKeyEvent.setType(COH_RADIUS_DOWN);
				EventSystem::getInstance()->fireEvent(mKeyEvent);
			}
			if (mEvent.key.keysym.sym == SDLK_d)
			{
				cout << "InputSystem: D" << endl;
				mKeyEvent.setType(DELETE_UNIT);
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