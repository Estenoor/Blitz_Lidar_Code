#include "WPILib.h"
#include "manipulator.hpp"

FRC::manipulator::manipulator():
//Declare Object Ports
gear(5),
GearSwitch(0),
ball(0),
climbMotor(2)

{

}

void FRC::manipulator::climb(){
		climbMotor.Set(1);
}

void FRC::manipulator::GearReset(double speed){
	if(GearSwitch.Get()){
		gear.Set(speed * .25);
	}else if(!GearSwitch.Get()){
		gear.SetEncPosition(0);
		gear.Set(0);
	}
}

void FRC::manipulator::GearOut(double speed){
	if(gear.GetEncPosition() > -350){
		gear.Set(speed * .75);
	}
	else{
		gear.Set(0);
	}
}

void FRC::manipulator::ballEject(){
	ball.Set(0.7);
}







