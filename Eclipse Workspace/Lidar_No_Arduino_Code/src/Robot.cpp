//#include "5148.Win"
#include "WPILib.h"
#include "inputManager.hpp"
#include "driveManager.hpp"
#include "manipulator.hpp"
#include "cameraManager.hpp"
#include "arduinoManager.hpp"
#include "Lidar_Manager_V2.hpp"

class Robot: public SampleRobot
{
	FRC::inputManager inputMan;
	FRC::driveManager driveMan;
	FRC::manipulator manipulator;
	FRC::LidarManager Lidar;
	//FRC::cameraManager cameraMan;
	Relay spike;
	Timer *lightTimer;
	FRC::Arduino DSTemp;

public:
	Robot() :
		inputMan(),
		driveMan(),
		manipulator(),
		//cameraMan(),
		spike(0),
		DSTemp(0x01),
		Lidar()

{

}

void Autonomous()
{
	while (IsEnabled() && IsAutonomous())
	{
		bool isAuto = true;
		SmartDashboard::PutBoolean("isAuto", isAuto);
		Lidar.ProportionalSlowAntiDavid(3, 1.2, 0.5);

	}
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
	driveMan.leftBackM.SetEncPosition(0);
	driveMan.leftFrontM.SetEncPosition(0);
	driveMan.rightBackM.SetEncPosition(0);
	driveMan.rightFrontM.SetEncPosition(0);

	while (IsOperatorControl() && IsEnabled())
	{
		//Controls Led Strip
		spike.Set(Relay::kForward);

		/*
		if (lightTimer->Get() / 5 == 1)
		{
			spike.Set(Relay::kOff);
		}
		if (lightTimer->Get() / 5.1 == 1)
		{
				spike.Set(Relay::kForward);
		}
		/**/

		//Strait Drive at Angle
		isPressed = inputMan.JoyStick.GetRawButton(1);

		if(isPressed != isPrePressed && !isPrePressed)
		{
			CurrAngle = driveMan.getAngle();
			isPrePressed = true;
		}
		else if(isPressed != isPrePressed && !isPressed)
		{
			isPrePressed = false;
		}

		driveMan.Angle = driveMan.getAngle();

		//Toggle Encoder
		if(inputMan.JoyStick.GetRawButton(6) != preToggle  && !preToggle)
		{
			preToggle = true;
			if(!toggleOn)
			{
				toggleOn = true;
			}
			else if(toggleOn)
			{
				toggleOn = false;
			}
		}
		else if(inputMan.JoyStick.GetRawButton(6) != preToggle && !inputMan.JoyStick.GetRawButton(6))
		{
			preToggle = false;
		}
		else
		{

		}

		//Drive Code
		driveMan.ramp();

		if(inputMan.JoyStick.GetRawButton(1))
		{
			//driveMan.straightDrive(CurrAngle);
		}
		else
		{
			driveMan.mecanumDrive(driveMan.JoyY, driveMan.JoyX, driveMan.joyRotate, toggleOn);
		}

		//Resets Encoders on button push
		if(inputMan.JoyStick.GetRawButton(3))
		{
			driveMan.leftBackM.SetEncPosition(0);
			driveMan.leftFrontM.SetEncPosition(0);
			driveMan.rightBackM.SetEncPosition(0);
			driveMan.rightFrontM.SetEncPosition(0);
		}

		//Gear Manager
		if(inputMan.xBox.GetRawAxis(5) > .1)
		{
			manipulator.GearReset(-inputMan.xBox.GetRawAxis(5));
		}
		else if(inputMan.xBox.GetRawAxis(5) < -.1)
		{
			manipulator.GearOut(-inputMan.xBox.GetRawAxis(5));
		}
		else
		{
			manipulator.gear.Set(0);
		}
		if(inputMan.xBox.GetRawAxis(3) > .1)
		{
			manipulator.ballEject();
		}
		else
		{
			manipulator.ball.Set(0);
		}

		/*
		if(inputMan.JoyStick.GetRawButton(2) && pulse <= 3024)
		{
			pulse = driveMan.leftBackM.GetEncPosition();
			run = true;
		}
		else if(!run)
		{
			driveMan.leftBackM.SetEncPosition(0);
			driveMan.leftFrontM.SetEncPosition(0);
			driveMan.rightBackM.SetEncPosition(0);
			driveMan.rightFrontM.SetEncPosition(0);
		}
		/**/

		//Directional Control
		if(inputMan.JoyStick.GetRawAxis(3) > 0)
		{
			driveMan.dir = -1;
		}
		else
		{
			driveMan.dir = 1;
		}
		if(inputMan.xBox.GetRawButton(5) && manipulator.PDP.GetCurrent(0) < 50 && manipulator.PDP.GetCurrent(1) < 50)
		{
			manipulator.climb();
		}
		else if (manipulator.PDP.GetCurrent(0) > 50 && manipulator.PDP.GetCurrent(1) < 50)
		{
			manipulator.climbMotor.Set(0);
		}
		else if(inputMan.xBox.GetRawButton(7))
		{
			manipulator.climbMotor.Set(0);
		}
		Wait(0.005);

		double tempArray[4];
		std::string valArray[4] {"LeftFront", "LeftBack", "RightBack", "RightFront"};
		DSTemp.getTemp(tempArray);
		for (int a = 0; a < 4; a++)
		{
			SmartDashboard::PutNumber(valArray[a], tempArray[a]);
		}

		//JoySticks(postRamp)
		SmartDashboard::PutNumber("JoyX", driveMan.JoyX);
		SmartDashboard::PutNumber("JoyY", driveMan.JoyY);
		SmartDashboard::PutNumber("joyRotate", driveMan.joyRotate);
		SmartDashboard::PutBoolean("GearSwitch", manipulator.GearSwitch.Get());
		SmartDashboard::PutNumber("Average Distance", driveMan.getEncDistance());

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


		SmartDashboard::PutNumber("Angle Delta", driveMan.rotation);
		SmartDashboard::PutNumber("PreAngle", CurrAngle);
		SmartDashboard::PutNumber("Angle", driveMan.Angle);
		SmartDashboard::PutNumber("Angle Rate", driveMan.ahrs.GetRate());
		SmartDashboard::PutBoolean("ToggleOn", toggleOn);
		SmartDashboard::PutNumber("LeftFront Encoder", driveMan.leftFrontM.GetEncVel());
		SmartDashboard::PutNumber("LeftBack Encoder", driveMan.leftBackM.GetEncVel());
		SmartDashboard::PutNumber("RightFront Encoder", driveMan.rightFrontM.GetEncVel());
		SmartDashboard::PutNumber("RightBack Encoder", driveMan.rightBackM.GetEncVel());

		SmartDashboard::PutNumber("LeftFront EncoderFreq", driveMan.EncoderFreq[0]);
		SmartDashboard::PutNumber("LeftBack EncoderFreq", driveMan.EncoderFreq[1]);
		SmartDashboard::PutNumber("RightFront EncoderFreq", driveMan.EncoderFreq[2]);
		SmartDashboard::PutNumber("RightBack EncoderFreq", driveMan.EncoderFreq[3]);

		SmartDashboard::PutNumber("LeftFront Pos", driveMan.leftFrontM.GetEncPosition());
		SmartDashboard::PutNumber("LeftBack Pos", driveMan.leftBackM.GetEncPosition());
		SmartDashboard::PutNumber("RightFront Pos", driveMan.rightFrontM.GetEncPosition());
		SmartDashboard::PutNumber("RightBack Pos", driveMan.rightBackM.GetEncPosition());
		SmartDashboard::PutNumber("Gear Pos", manipulator.gear.GetEncPosition());
	}
}

private :

static void VisionThread()
	{
		cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera("10.51.48.11");
		camera.SetResolution(640,480);
		camera.SetFPS(30);

		cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
		cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);
		//cv::Mat mat;

		/*
		while (true)
		{
			if (cvSink.GrabFrame(mat) == 0)
			{
				outputStream.NotifyError(cvSink.GetError());
				continue;
			}
		rectangle(mat, cv::Point(100, 100), cv::Point(400, 400), cv::Scalar(255,255,255), 5);
		outputStream.PutFrame(mat);
		}
		/**/
	}

	void RobotInit()
	{
		std::thread visionThread(VisionThread);
		visionThread.detach();
	}
};

START_ROBOT_CLASS(Robot)

//code.work(plz);
