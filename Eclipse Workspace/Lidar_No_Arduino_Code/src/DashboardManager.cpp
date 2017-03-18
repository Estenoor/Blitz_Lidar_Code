/*
 * DashboardManager.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Sam
 */

#include "DashboardManager.hpp"

FRC::DashboardManager::DashboardManager() :

inputMan(),
driveMan(),
manipulator(),
autoMan(),
lidarMan(),
cameraMan()

{

}

void FRC::DashboardManager::autoSmartDashboard()
{
	SmartDashboard::PutNumber("Lidar Distance", lidarMan.getLidDistance());
	SmartDashboard::PutNumber("Control Limit", lidarMan.ProportionalSlowAntiDavid());
}

void FRC::DashboardManager::teleSmartDashboard()
{

	//Angle
	SmartDashboard::PutNumber("Rotation", driveMan.rotation);
	SmartDashboard::PutNumber("Strait Drive Angle", driveMan.getAngle());
	SmartDashboard::PutNumber("Angle Rate", driveMan.ahrs.GetRate());

	//Control Info
	SmartDashboard::PutBoolean("Using Encoders", autoMan.Auto.GetRawButton(5));
	SmartDashboard::PutNumber("Control Limit", lidarMan.ProportionalSlowAntiDavid());

	//JoySticks(postRamp)
	SmartDashboard::PutNumber("JoyX", driveMan.JoyX);
	SmartDashboard::PutNumber("JoyY", driveMan.JoyY);
	SmartDashboard::PutNumber("joyRotate", driveMan.joyRotate);
	SmartDashboard::PutBoolean("GearSwitch", manipulator.GearSwitch.Get());
	SmartDashboard::PutNumber("Nav Angle", driveMan.getAngle());
	SmartDashboard::PutBoolean("Bypass", driveMan.bypassing);
	SmartDashboard::PutNumber("Joystick Radians", inputMan.joystickRadians());


	//Motor Info
	SmartDashboard::PutNumber("LeftFront spdRef", driveMan.spdRef[0]);
	SmartDashboard::PutNumber("LeftFront error", driveMan.error[0]);
	SmartDashboard::PutNumber("LeftFront SPFeedBack", driveMan.SPFeedBack[0]);
	SmartDashboard::PutNumber("LeftFront propOut", driveMan.propOut[0]);


	//Manipulator
	SmartDashboard::PutNumber("Gear Pot", manipulator.pot.GetValue());

	//Distance
	SmartDashboard::PutNumber("Encoder Distance", autoMan.getEncDistance());
	SmartDashboard::PutNumber("Dist From Center", cameraMan.getDistFromCenter());
	SmartDashboard::PutNumber("Lidar Distance", lidarMan.getLidDistance());

	//Motor Speeds
	SmartDashboard::PutNumber("LeftFront  Speed", driveMan.speeds[0]);
	SmartDashboard::PutNumber("LeftBack   Speed", driveMan.speeds[1]);
	SmartDashboard::PutNumber("RightFront Speed", driveMan.speeds[2]);
	SmartDashboard::PutNumber("RightBack  Speed", driveMan.speeds[3]);

	//PWM Output
	SmartDashboard::PutNumber("LeftFront PWMout", driveMan.PWMout[0]);
	SmartDashboard::PutNumber("LeftBack PWMout", driveMan.PWMout[1]);
	SmartDashboard::PutNumber("RightFront PWMout", driveMan.PWMout[2]);
	SmartDashboard::PutNumber("RightBack PWMout", driveMan.PWMout[3]);

	//Encoder Velocity
	SmartDashboard::PutNumber("leftFront Encoder Velocity", driveMan.leftFrontM.GetEncVel());
	SmartDashboard::PutNumber("leftBack Encoder Velocity", driveMan.leftBackM.GetEncVel());
	SmartDashboard::PutNumber("RightFront Encoder Velocity", driveMan.rightFrontM.GetEncVel());
	SmartDashboard::PutNumber("RightBack Encoder Velocity", driveMan.rightBackM.GetEncVel());
}

void FRC::DashboardManager::rawInputSmartDashboard()
{
	//Raw JoySticks
	SmartDashboard::PutNumber("JoyX Raw", driveMan.JoyXRaw);
	SmartDashboard::PutNumber("JoyY Raw", driveMan.JoyYRaw);
	SmartDashboard::PutNumber("JoyRotate Raw", driveMan.JoyRotateRaw);
	SmartDashboard::PutNumber("Direction Axis Raw", inputMan.JoyStick.GetRawAxis(3));


	//Raw Encoder Position
	SmartDashboard::PutNumber("LeftFront Encoder Raw", driveMan.leftFrontM.GetEncPosition());
	SmartDashboard::PutNumber("LeftBack Encoder Raw", driveMan.leftBackM.GetEncPosition());
	SmartDashboard::PutNumber("RightFront Encoder Raw", driveMan.rightFrontM.GetEncPosition());
	SmartDashboard::PutNumber("RightBack Encoder Raw",  driveMan.rightBackM.GetEncPosition());

}
