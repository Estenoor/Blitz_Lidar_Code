#include <WPILib.h>


class Robot: public frc::SampleRobot {

public:
	Robot()
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
