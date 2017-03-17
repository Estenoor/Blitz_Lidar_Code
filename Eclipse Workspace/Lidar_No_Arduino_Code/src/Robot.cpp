//#include "5148.Win"
#include "WPILib.h"
#include "inputManager.hpp"
#include "driveManager.hpp"
#include "manipulator.hpp"
#include "cameraManager.hpp"
#include "autoManager.hpp"

class Robot: public SampleRobot
{
	FRC::inputManager inputMan;
	FRC::driveManager driveMan;
	FRC::manipulator manipulator;
	FRC::autoManager autoMan;
	FRC::cameraManager cameraMan;
	//Relay spike;
	Timer *lightTimer;

public:
	Robot() :
		inputMan(),
		driveMan(),
		manipulator(),
		autoMan(),
		cameraMan()
//spike(0)
{

}
	void Autonomous(){
		std::thread visionThread(VisionThread);
		visionThread.detach();
		bool gotAngle = false;
		double Angle = 0;
		driveMan.resetEnc();
		bool step1 = true;
		bool step2 = false;
		bool step3 = false;

		while (IsAutonomous() && IsEnabled()){
			SmartDashboard::PutNumber("average distance", autoMan.getEncDistance());

			if(autoMan.Auto.GetRawButton(1) && !autoMan.Auto.GetRawButton(2) && !autoMan.Auto.GetRawButton(3)){
				if(!gotAngle){
					Angle = driveMan.getAngle();
					gotAngle = true;
				}

				if(autoMan.getEncDistance() < 18.5 && step1){
					autoMan.driveDistance(18.5, Angle);
				}else{
					step1 = false;
				}

				if(fabs(driveMan.getAngle()) < 120 - 3 && step2){
					autoMan.rotate(120);
					gotAngle = false;
					driveMan.resetEnc();
				}else{
					step2 = false;
				}

				if(autoMan.getEncDistance() < 9 && step3){
					autoMan.driveDistance(9, Angle);
				}else {
					step3 = false;
				}
			} else if(!autoMan.Auto.GetRawButton(1) && true && !autoMan.Auto.GetRawButton(3)){
				if(!gotAngle){
					Angle = driveMan.getAngle();
					gotAngle = true;
				}

				if(autoMan.getEncDistance() < .5 && step1){
					autoMan.driveDistance(.5, Angle);
				}else{
					step1 = false;
				}
			} else if(!autoMan.Auto.GetRawButton(1) && !autoMan.Auto.GetRawButton(2) && autoMan.Auto.GetRawButton(3)){
				if(!gotAngle){
					Angle = driveMan.getAngle();
					gotAngle = true;
				}

				if(autoMan.getEncDistance() < 18.5 && step1){
					autoMan.driveDistance(18.5, Angle);
				}else{
					step1 = false;
				}

				if(fabs(driveMan.getAngle()) > 240 + 3 && step2){
					autoMan.rotate(240);
					gotAngle = false;
					driveMan.resetEnc();
				}else{
					step2 = false;
				}

				if(autoMan.getEncDistance() < 9 && step3){
					autoMan.driveDistance(9, Angle);
				}else {
					step3 = false;
				}
			}
		}
	}


	void OperatorControl()
	{
		//lightTimer->Reset();
		//lightTimer->Start();
		std::thread visionThread(VisionThread);
		visionThread.detach();
		double const circFeet = 2.09;
		driveMan.mecanumDrive(0, 0, 0, false);
		bool isPressed = false;
		bool isPrePressed = false;
		double CurrAngle = 0;
		bool toggleOn = false;
		bool preToggle = false;
		int pulse = 0;
		bool run = false;
		bool hello;
		float converter = 3024/1880;
		driveMan.leftBackM.SetEncPosition(0);
		driveMan.leftFrontM.SetEncPosition(0);
		driveMan.rightBackM.SetEncPosition(0);
		driveMan.rightFrontM.SetEncPosition(0);

		while (IsOperatorControl() && IsEnabled())
		{
			//Limit Switch Resets Encoders
			if(manipulator.GearSwitch.Get()==false)
				manipulator.gear.SetEncPosition(0);

			if(inputMan.JoyStick.GetRawButton(10)){
				manipulator.gear.Set(.3);
			}else if(inputMan.JoyStick.GetRawButton(9)){
				manipulator.gear.Set(-.3);
			}else{
				manipulator.gear.Set(0);
			}

			//Encoder Toggle
			toggleOn = autoMan.Auto.GetRawButton(5);

			//leds
			//spike.Set(Relay::kForward);
			/*if (lightTimer->Get() / 5 == 1) {
				spike.Set(Relay::kOff);
			}
			if (lightTimer->Get() / 5.1 == 1) {
				spike.Set(Relay::kForward);
			}*/

			//straight drive angle
			isPressed = inputMan.JoyStick.GetRawButton(1);

			if(isPressed != isPrePressed && !isPrePressed){
				CurrAngle = driveMan.getAngle();
				isPrePressed = true;
			}else if(isPressed != isPrePressed && !isPressed){
				isPrePressed = false;
			}

			driveMan.Angle = driveMan.getAngle();

			/*//encoder toggle
			if(inputMan.JoyStick.GetRawButton(6) != preToggle  && !preToggle){
				preToggle = true;
				if(!toggleOn){
					toggleOn = true;
				}else if(toggleOn){
					toggleOn = false;
				}
			}else if(inputMan.JoyStick.GetRawButton(6) != preToggle && !inputMan.JoyStick.GetRawButton(6)){
				preToggle = false;
			}else{

			}*/

			//drive code
			driveMan.ramp();

//			if((inputMan.JoyStick.GetDirectionDegrees()>-15 && inputMan.JoyStick.GetDirectionDegrees()<15) || (inputMan.JoyStick.GetDirectionDegrees()>165 && inputMan.JoyStick.GetDirectionDegrees()<195))
//			{
//				if(inputMan.JoyStick.GetRawAxis(0)>0)
//					driveMan.straightDrive(0, 0, driveMan.JoyY);
//				else if(inputMan.JoyStick.GetRawAxis(0)<0)
//					driveMan.straightDrive(180, 0, driveMan.JoyY);
//			}
			if(inputMan.JoyStick.GetRawButton(12)) {
				cameraMan.centerWithTape();
			}
			else if(inputMan.JoyStick.GetRawButton(2))
				driveMan.FieldControl(driveMan.JoyX,driveMan.JoyY,driveMan.joyRotate);
			else if(inputMan.JoyStick.GetRawButton(1)){
				driveMan.straightDrive(CurrAngle, driveMan.JoyX, driveMan.JoyY);
				hello = true;
			}else if(inputMan.JoyStick.GetRawButton(3)){
				driveMan.straightDrive(CurrAngle, 0, .6);
				//driveMan.mecanumDrive(.2, 0 , 0, false);
			}else if(inputMan.JoyStick.GetRawButton(4)){
				driveMan.straightDrive(CurrAngle, 0, -.6);
				//driveMan.mecanumDrive(-.2, 0, 0, false);
			}else if(inputMan.JoyStick.GetRawButton(7)){
				autoMan.driveDistance(2, CurrAngle);
			}else {
				CurrAngle = driveMan.getAngle();
				driveMan.mecanumDrive(driveMan.JoyY, driveMan.JoyX, driveMan.joyRotate, toggleOn);
				hello = false;
			}

			//reset encoders
			if(inputMan.JoyStick.GetRawButton(11)){
				driveMan.leftBackM.SetEncPosition(0);
				driveMan.leftFrontM.SetEncPosition(0);
				driveMan.rightBackM.SetEncPosition(0);
				driveMan.rightFrontM.SetEncPosition(0);
				run = false;
			}

			//gear manipulator
			if(inputMan.xBox.GetRawAxis(5) < -.1){
				manipulator.GearOut(-inputMan.xBox.GetRawAxis(5));
			}else if(inputMan.xBox.GetRawAxis(5) > .1){
				manipulator.GearReset(-inputMan.xBox.GetRawAxis(5));
			}

			if(inputMan.xBox.GetRawAxis(3) > .1){
				manipulator.ballEject();
			}
			else{
				manipulator.ball.Set(0);	//tommy.wuzH3r3
			}


			/*if(inputMan.JoyStick.GetRawButton(2) && pulse <= 3024){
				pulse = driveMan.leftBackM.GetEncPosition();
				run = true;
			}else if(!run){
				driveMan.leftBackM.SetEncPosition(0);
				driveMan.leftFrontM.SetEncPosition(0);
				driveMan.rightBackM.SetEncPosition(0);
				driveMan.rightFrontM.SetEncPosition(0);
			}*/

			//direction control
			if(inputMan.JoyStick.GetRawAxis(3) > 0){
				driveMan.dir = -1;
			}else{
				driveMan.dir = 1;
			}


			if(inputMan.xBox.GetRawAxis(2) && manipulator.PDP.GetCurrent(0) < 50 && manipulator.PDP.GetCurrent(1) < 50){
				manipulator.climb();
			}else{ //if(manipulator.PDP.GetCurrent(0) > 50 && manipulator.PDP.GetCurrent(1) < 50){
				manipulator.climbMotor.Set(0);
			}

			Wait(0.005);

			//JoySticks(postRamp)
			SmartDashboard::PutNumber("JoyX", driveMan.JoyX);
			SmartDashboard::PutNumber("JoyY", driveMan.JoyY);
			SmartDashboard::PutNumber("joyRotate", driveMan.joyRotate);
			SmartDashboard::PutBoolean("GearSwitch", manipulator.GearSwitch.Get());
			SmartDashboard::PutBoolean("straight drive", hello);
			SmartDashboard::PutNumber("Nav Angle", driveMan.getAngle());
			SmartDashboard::PutBoolean("bypass", driveMan.bypassing);

			//Raw JoySticks
			//			SmartDashboard::PutNumber("JoyXRaw", driveMan.JoyXRaw);
			//			SmartDashboard::PutNumber("JoyYRaw", driveMan.JoyYRaw);
			//			SmartDashboard::PutNumber("JoyRotateRaw", driveMan.JoyRotateRaw);
			//			SmartDashboard::PutNumber("Direction axis", inputMan.JoyStick.GetRawAxis(3));
			//
			//			SmartDashboard::PutNumber("LeftFront speeds", driveMan.speeds[0]);
			//			SmartDashboard::PutNumber("LeftBack speeds", driveMan.speeds[1]);
			//			SmartDashboard::PutNumber("RightFront speeds", driveMan.speeds[2]);
			//			SmartDashboard::PutNumber("RightBack speeds", driveMan.speeds[3]);
			//
			//			SmartDashboard::PutNumber("LeftFront PWMout", driveMan.PWMout[0]);
			//			SmartDashboard::PutNumber("LeftBack PWMout", driveMan.PWMout[1]);
			//			SmartDashboard::PutNumber("RightFront PWMout", driveMan.PWMout[2]);
			//			SmartDashboard::PutNumber("RightBack PWMout", driveMan.PWMout[3]);
			//
			//
			//			SmartDashboard::PutNumber("LeftFront spdRef", driveMan.spdRef[0]);
			//			SmartDashboard::PutNumber("LeftFront error", driveMan.error[0]);
			//			SmartDashboard::PutNumber("LeftFront SPFeedBack", driveMan.SPFeedBack[0]);
			//			SmartDashboard::PutNumber("LeftFront propOut", driveMan.propOut[0]);
			//
			//			SmartDashboard::PutNumber("zachG", driveMan.rotation);
			//			SmartDashboard::PutNumber("PreAngle", CurrAngle);
			SmartDashboard::PutNumber("joy angle", inputMan.joystickRadians());
//			SmartDashboard::PutNumber("Angle Rate", driveMan.ahrs.GetRate());
//
//			SmartDashboard::PutBoolean("toggleOn", toggleOn);
//
			SmartDashboard::PutNumber("leftFront Encoder", driveMan.leftFrontM.GetEncVel());
			SmartDashboard::PutNumber("leftBack Encoder", driveMan.leftBackM.GetEncVel());
			SmartDashboard::PutNumber("RightFront Encoder", driveMan.rightFrontM.GetEncVel());
			SmartDashboard::PutNumber("RightBack Encoder", driveMan.rightBackM.GetEncVel());

			//			SmartDashboard::PutNumber("leftFront EncoderFreq", driveMan.EncoderFreq[0]);
			//			SmartDashboard::PutNumber("leftBack EncoderFreq", driveMan.EncoderFreq[1]);
			//			SmartDashboard::PutNumber("RightFront EncoderFreq", driveMan.EncoderFreq[2]);
			//			SmartDashboard::PutNumber("RightBack EncoderFreq", driveMan.EncoderFreq[3]);

			SmartDashboard::PutNumber("leftFront Pos", driveMan.leftFrontM.GetEncPosition());
			SmartDashboard::PutNumber("leftBack Pos", driveMan.leftBackM.GetEncPosition());
			SmartDashboard::PutNumber("RightFront Pos", driveMan.rightFrontM.GetEncPosition());
			SmartDashboard::PutNumber("RightBack Pos",  driveMan.rightBackM.GetEncPosition());

			SmartDashboard::PutNumber("Average Distance", autoMan.getEncDistance());
			SmartDashboard::PutNumber("Dist From Center", cameraMan.getDistFromCenter());

			SmartDashboard::PutNumber("Gear Pot", manipulator.pot.GetValue());
		}
	}

	static void VisionThread() {
		cs::AxisCamera axisCamera = CameraServer::GetInstance()->AddAxisCamera("10.51.48.11");
		cs::UsbCamera usbCamera = CameraServer::GetInstance()->StartAutomaticCapture();
		axisCamera.SetResolution(480,360);
		usbCamera.SetResolution(640, 480);

		cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);
	}
};

//code.work(plz);
START_ROBOT_CLASS(Robot)




/*Auto Measurements / Plan:
Center:
3.5 ft. forward
Left Corner:
13.5 ft. forward
135 degrees clockwise
10 ft. forward
Right Corner:
10 ft. forward
45 degrees clockwise
7.5 ft. forward

The above measurements are approximate, use only for starting the frame of the autonomous code.


 */
