#include "WPILib.h"
#include "manipulator.hpp"
#include "inputManager.hpp"
FRC::manipulator::manipulator():
//Declare Object Ports
gear(5),
GearSwitch(0),
ball(1),
climbMotor(2),
inputManager(),
pot(0)

{

}

void FRC::manipulator::climb()
{
	if(inputManager.xBox.GetRawAxis(2) > .8)
	{
		climbMotor.Set(1);
	}
	else
	{
		climbMotor.Set(.1);
	}
}

void FRC::manipulator::GearReset(double speed)
{
	if(pot.GetValue() > 12)	//change number for constraints
	{
		gear.Set(speed * 0.30);
	}
	else
	{
		gear.Set(0);
	}
}

void FRC::manipulator::GearOut(double speed)
{
	if(pot.GetValue() < 3900)	//change number for constraints
	{
		gear.Set(speed * 0.5);
	}
	else
	{
		gear.Set(0);
	}
}

void FRC::manipulator::ballEject()
{
	ball.Set(0.7);
}
