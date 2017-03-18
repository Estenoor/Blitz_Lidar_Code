#ifndef SRC_INPUTMANAGER_HPP_
#define SRC_INPUTMANAGER_HPP_
#include "WPILib.h"
#include <cmath>


namespace FRC
{
	class inputManager
	{
		public:
			inputManager();
			Joystick JoyStick, xBox;
			double joystickRadians();
	};
}

#endif




