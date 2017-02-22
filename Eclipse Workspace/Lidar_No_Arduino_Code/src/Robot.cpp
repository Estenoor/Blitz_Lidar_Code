//#include "5148.Win"
#include "WPILib.h"
#include "inputManager.hpp"
#include "driveManager.hpp"
#include "manipulator.hpp"
#include "cameraManager.hpp"

class Robot: public SampleRobot
{
	FRC::inputManager inputMan;
	FRC::driveManager driveMan;
	FRC::manipulator manipulator;
	//FRC::cameraManager cameraMan;
	Relay spike;
	Timer *lightTimer;

public:
	Robot() :
		inputMan(),
		driveMan(),
		manipulator(),
		//cameraMan(),
		spike(0)
{

}


	void OperatorControl()
	{
		//lightTimer->Reset();
		//lightTimer->Start();
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
		driveMan.leftBackM.SetEncPosition(0);
		driveMan.leftFrontM.SetEncPosition(0);
		driveMan.rightBackM.SetEncPosition(0);
		driveMan.rightFrontM.SetEncPosition(0);

		/*while(driveMan.GearSwitch.Get()){
			driveMan.gear.Set(-.1);
		}
		driveMan.gear.Set(0);*/

		while (IsOperatorControl() && IsEnabled())
		{
			//leds
			spike.Set(Relay::kForward);
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

			//encoder toggle
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

			}

			//drive code
			driveMan.ramp();

			if(inputMan.JoyStick.GetRawButton(1)){
				//driveMan.straightDrive(CurrAngle);
				hello = true;
			}else{
				driveMan.mecanumDrive(driveMan.JoyY, driveMan.JoyX, driveMan.joyRotate, toggleOn);
				hello = false;
			}

			//reset encoders
			if(inputMan.JoyStick.GetRawButton(3)){
				driveMan.leftBackM.SetEncPosition(0);
				driveMan.leftFrontM.SetEncPosition(0);
				driveMan.rightBackM.SetEncPosition(0);
				driveMan.rightFrontM.SetEncPosition(0);
				run = false;
			}

			//gear manipulator
			if(inputMan.xBox.GetRawAxis(5) > .1){
				manipulator.GearReset(-inputMan.xBox.GetRawAxis(5));
			}else if(inputMan.xBox.GetRawAxis(5) < -.1){
				manipulator.GearOut(-inputMan.xBox.GetRawAxis(5));
			}else{
				manipulator.gear.Set(0);
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

			if(inputMan.xBox.GetRawButton(5) && manipulator.PDP.GetCurrent(0) < 50 && manipulator.PDP.GetCurrent(1) < 50){
				manipulator.climb();
			}else if(manipulator.PDP.GetCurrent(0) > 50 && manipulator.PDP.GetCurrent(1) < 50){
				manipulator.climbMotor.Set(0);
			}else if(inputMan.xBox.GetRawButton(7)){
				manipulator.climbMotor.Set(0);
			}



			Wait(0.005);
			//JoySticks(postRamp)
			SmartDashboard::PutNumber("JoyX", driveMan.JoyX);
			SmartDashboard::PutNumber("JoyY", driveMan.JoyY);
			SmartDashboard::PutNumber("joyRotate", driveMan.joyRotate);
			SmartDashboard::PutBoolean("GearSwitch", manipulator.GearSwitch.Get());
			SmartDashboard::PutBoolean("straight drive", hello);

			SmartDashboard::PutNumber("leftFront distance", driveMan.getDistance(driveMan.leftFrontM.GetEncPosition()));

			//Raw JoySticks
			SmartDashboard::PutNumber("JoyXRaw", driveMan.JoyXRaw);
			SmartDashboard::PutNumber("JoyYRaw", driveMan.JoyYRaw);
			SmartDashboard::PutNumber("JoyRotateRaw", driveMan.JoyRotateRaw);
			SmartDashboard::PutNumber("Direction axis", inputMan.JoyStick.GetRawAxis(3));

			SmartDashboard::PutNumber("LeftFront speeds", driveMan.speeds[0]);
			SmartDashboard::PutNumber("LeftBack speeds", driveMan.speeds[1]);
			SmartDashboard::PutNumber("RightFront speeds", driveMan.speeds[2]);
			SmartDashboard::PutNumber("RightBack speeds", driveMan.speeds[3]);

			SmartDashboard::PutNumber("LeftFront PWMout", driveMan.PWMout[0]);
			SmartDashboard::PutNumber("LeftBack PWMout", driveMan.PWMout[1]);
			SmartDashboard::PutNumber("RightFront PWMout", driveMan.PWMout[2]);
			SmartDashboard::PutNumber("RightBack PWMout", driveMan.PWMout[3]);


			SmartDashboard::PutNumber("zachG", driveMan.rotation);
			SmartDashboard::PutNumber("PreAngle", CurrAngle);
			SmartDashboard::PutNumber("Angle", driveMan.Angle);
			SmartDashboard::PutNumber("Angle Rate", driveMan.ahrs.GetRate());

			SmartDashboard::PutBoolean("toggleOn", toggleOn);

			SmartDashboard::PutNumber("leftFront Encoder", driveMan.leftFrontM.GetEncVel());
			SmartDashboard::PutNumber("leftBack Encoder", driveMan.leftBackM.GetEncVel());
			SmartDashboard::PutNumber("RightFront Encoder", driveMan.rightFrontM.GetEncVel());
			SmartDashboard::PutNumber("RightBack Encoder", driveMan.rightBackM.GetEncVel());

			SmartDashboard::PutNumber("leftFront EncoderFreq", driveMan.EncoderFreq[0]);
			SmartDashboard::PutNumber("leftBack EncoderFreq", driveMan.EncoderFreq[1]);
			SmartDashboard::PutNumber("RightFront EncoderFreq", driveMan.EncoderFreq[2]);
			SmartDashboard::PutNumber("RightBack EncoderFreq", driveMan.EncoderFreq[3]);


			SmartDashboard::PutNumber("leftFront Pos", driveMan.leftFrontM.GetEncPosition());
			SmartDashboard::PutNumber("leftBack Pos", driveMan.leftBackM.GetEncPosition());
			SmartDashboard::PutNumber("RightFront Pos", driveMan.rightFrontM.GetEncPosition());
			SmartDashboard::PutNumber("RightBack Pos", driveMan.rightBackM.GetEncPosition());
			SmartDashboard::PutNumber("gear Pos", manipulator.gear.GetEncPosition());

			SmartDashboard::PutNumber("LeftFront distance", driveMan.getDistance(driveMan.leftFrontM.GetEncPosition()));
			SmartDashboard::PutNumber("LeftBack distance", driveMan.getDistance(driveMan.leftBackM.GetEncPosition()));
			SmartDashboard::PutNumber("RightFront distance", driveMan.getDistance(driveMan.rightFrontM.GetEncPosition()));
			SmartDashboard::PutNumber("RightBack distance", driveMan.getDistance(driveMan.rightBackM.GetEncPosition()));


		}
	}

private :
	static void VisionThread() {
		cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera("10.51.48.11");
		camera.SetResolution(640,480);
		camera.SetFPS(30);

		cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
		cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);
		//cv::Mat mat;

		//while (true) {
		/*if (cvSink.GrabFrame(mat) == 0) {
				outputStream.NotifyError(cvSink.GetError());
				continue;
			}*/
		//rectangle(mat, cv::Point(100, 100), cv::Point(400, 400), cv::Scalar(255,255,255), 5);
		//outputStream.PutFrame(mat);
		//}
	}

	void RobotInit() {
		std::thread visionThread(VisionThread);
		visionThread.detach();
	}
};

START_ROBOT_CLASS(Robot)

//code.work(plz);
