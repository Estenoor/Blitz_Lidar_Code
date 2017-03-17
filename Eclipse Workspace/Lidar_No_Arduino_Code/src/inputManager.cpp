#include "WPILib.h"
#include "inputManager.hpp"
#include <cmath>

FRC::inputManager::inputManager():
//Declare Object Ports
JoyStick(0),
xBox(1)
{

}

double FRC::inputManager::joystickRadians()
{
	if(JoyStick.GetX()>0)
	{
		return (atan(-JoyStick.GetY()/-JoyStick.GetX())+1.5708);
	}
	else if(JoyStick.GetX()<0)
		return (atan(-JoyStick.GetY()/-JoyStick.GetX())+2.3562);

	else{
		return 0;
	}
}





