#include <driveManager.hpp>
#include <Joystick.h>
#include <Timer.h>
#include <cmath>
#include <cstdbool>
#include <cstdlib>
#include <inputManager.hpp>
#include <WPILib.h>
#include <CanTalon.h>
#include "AHRS.h"

FRC::driveManager::driveManager() :
//Declare Object Ports
leftBackM(3),
leftFrontM(1),
rightBackM(4),
rightFrontM(2),
ahrs {SPI::Port::kMXP},
inputManager()
{

}
int FRC::driveManager::getAngle(){

	return (int) ahrs.GetFusedHeading();
}

void FRC::driveManager::PIcorrection(int id){
	double const RateFrequency = 2000; //target Velocity
	double propGain = 1.0; //Proportional multiplier
	double const MaxHz = 2600.0; // max Hz
	//double const intGain = .005; // integral Gain
	//double const intLimit = 0.10; // integral limits

	if(speeds[id] - preSpeed[id] > .1){
		propGain = 2.0;
	}else{
		propGain = 1.0;
	}

	spdRef[id] = speeds[id] * (RateFrequency/MaxHz);

	SPFeedBack[id] = EncoderFreq[id]/RateFrequency;

	error[id] = spdRef[id] - SPFeedBack[id];

	/*if(!intReset && fabs(error[id]) < .1){
		intOut[id] = intOut[id] + (error[id]* intGain);
	}else{
		intOut[id] = 0;
	}

	if(intOut[id] > intLimit){
		intOut[id] = intLimit;
	}else if(intOut[id] < -intLimit){
		intOut[id] = -intLimit;
	}*/

	propOut[id] = error[id] * propGain;

	PIout[id] = propOut[id]; //+ intOut[id];

	PWMout[id] = spdRef[id] + PIout[id];

	preSpeed[id] = speeds[id];
}

void FRC::driveManager::ramp(){
	double deadBand = 0.2;	//deadband range
	double rampRate = 1/(.05 * 200.0); //.5 = time in seconds, 200 = scan rate

	JoyXRaw = dir * (inputManager.JoyStick.GetRawAxis(1));
	JoyYRaw = dir * (-inputManager.JoyStick.GetRawAxis(0));
	JoyRotateRaw = -(inputManager.JoyStick.GetRawAxis(2) * .5);

	//Left X axis
	if(fabs(JoyXRaw) < deadBand){
		JoyXRaw = 0;
	}
	if(JoyXRaw + .02 >= JoyX && JoyXRaw - .02 <= JoyX){

	}else if(JoyXRaw > JoyX){
		JoyX += rampRate;
	}else {
		JoyX -= rampRate;
	}

	//Left Y axis
	if(fabs(JoyYRaw) < deadBand){
		JoyYRaw = 0;
	}
	if(JoyYRaw + .02 >= JoyY && JoyYRaw - .02 <= JoyY){

	}else if(JoyYRaw > JoyY){
		JoyY += rampRate;
	}else {
		JoyY -= rampRate;
	}

	//Right X axis
	if(fabs(JoyRotateRaw) < .1){
		JoyRotateRaw = 0;
	}
	if(JoyRotateRaw + .02 >= joyRotate && JoyRotateRaw - .02 <= joyRotate){

	}else if(JoyRotateRaw > joyRotate){
		joyRotate += rampRate;
	}else{
		joyRotate -= rampRate;
	}
}


void FRC::driveManager::mecanumDrive(double y, double x, double rotate, bool bypass){
	double const Pow = 1;
	bypassing = bypass;
	if(fabs(rotate) < .1){
		rotation = 0.05 * (delta)+ .012 *ahrs.GetRate();
		//Mecanum equation(Left side inverted)
		speeds[0] = x + y - rotation;//Left Front
		speeds[1] = -(-x + y + rotation); //Left Rear
		speeds[2] = -x + y - rotation; //Right Front
		speeds[3] = -(x + y + rotation); //Right Rear

		//Normalize function: keeps values proportional and below 1
		maxMagnitude = std::fabs(FRC::driveManager::speeds[0]);
		int i;

		for (i = 1; i < 4; i++) {
			double temp = std::fabs(speeds[i]);
			if (maxMagnitude < temp) maxMagnitude = temp;
		}
		if (maxMagnitude > 1.0) {
			for (i = 0; i < 4; i++) {
				speeds[i] = speeds[i] / maxMagnitude;
			}
		}

		if(!bypass){
			EncoderFreq[0] = -leftFrontM.GetEncVel(); //Left Front
			EncoderFreq[1] = -leftBackM.GetEncVel(); //Left Rear
			EncoderFreq[2] = -rightFrontM.GetEncVel(); //Right Front
			EncoderFreq[3] = -rightBackM.GetEncVel(); //Right Rear

			PIcorrection(0);
			PIcorrection(1);
			PIcorrection(2);
			PIcorrection(3);



			leftFrontM.Set(PWMout[0] * Pow);
			leftBackM.Set(PWMout[1] * Pow);
			rightFrontM.Set(PWMout[2] * Pow);
			rightBackM.Set(PWMout[3] * Pow);
		}else{
			leftFrontM.Set(speeds[0] * Pow);
			leftBackM.Set(speeds[1] * Pow);
			rightFrontM.Set(speeds[2] * Pow);
			rightBackM.Set(speeds[3] * Pow);
		}
	}else{
		leftFrontM.Set(x + y + rotate);
		leftBackM.Set(-(-x + y - rotate));
		rightFrontM.Set(-x + y + rotate);
		rightBackM.Set(-(x + y - rotate));
	}
}

void FRC::driveManager::straightDrive(double PreAngle, double x, double y){
	zachG = PreAngle - Angle;

	ramp();

	rotation = 0.04 * (zachG)+ .012 *ahrs.GetRate();	//ryan.wasHere = true;

	/*if(x < .1 && x >= 0){
		x  *= -4;
	}else if(x > -.1 && x < 0){
		x *= 4;
	}

	if(y < .1 && y >= 0){
		y  *= -4;
	}else if(y > -.1 && y < 0){
		y *= 4;
	}*/

	if(fabs(y) > fabs(x)){
		mecanumDrive(y, 0, -rotation, true);
	}else{
		mecanumDrive(0, x, -rotation, true);
	}
}


void FRC::driveManager::resetEnc(){
	leftFrontM.SetEncPosition(0);
	leftBackM.SetEncPosition(0);
	rightFrontM.SetEncPosition(0);
	rightBackM.SetEncPosition(0);
}

void FRC::driveManager::FieldControl(double x, double y, double rotate){
	double r = sqrt(pow(x, 2) + pow(y, 2));

	if(inputManager.JoyStick.GetDirectionDegrees() < 0){
		ang = 360 + inputManager.JoyStick.GetDirectionDegrees();
	}else{
		ang = inputManager.JoyStick.GetDirectionDegrees();
	}

	ang -= getAngle();

	y = r * cos(ang * (pi/180));
	x = r * sin(ang * (pi/180));

	mecanumDrive(y, x, rotate, false);
}
