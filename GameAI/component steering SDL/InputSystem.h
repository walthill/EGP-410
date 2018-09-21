#ifndef INPUT_SYS
#define INPUT_SYS

#include "EventSystem.h"
#include "Event.h"
#include "MouseEvent.h"
#include "SDL.h"

/*
Object headers include Trackable in order
to use time and memory managment tool
*/

class InputSystem : public Trackable
{
	private:
		Event mKeyEvent;
		MouseEvent mMouseEvent;

		SDL_Event mEvent;

		//Controller data
		//Analog joystick dead zone
		int mLeftStickXDeadZone = 8000, mLeftStickYDeadZone = 8000, 
			mRightStickXDeadZone = 8000, mRightStickYDeadZone = 8000;

		SDL_Joystick *mGameController; //need Left, Right stick, A, RT
		Sint16 xAxis, yAxis;

	public:

		InputSystem();
		~InputSystem();

		//Init and cleanup
		bool initInputSystem();
		void cleanupInputSystem();

		//Input and mouse position
		void getInputEvents();
		
		//Call mouse and key events
		void update(double elapsedTime);
};

#endif // !INPUT_SYS
