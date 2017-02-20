//Include Files
#include "WPILib.h"
#include "Lidar_Manager.hpp"



class Robot: public SampleRobot
{
	FRC::LidarManager Lidar;


public:
	Robot() :

		Lidar()
		{

		}



	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{

		}
	}
};
START_ROBOT_CLASS(Robot)
