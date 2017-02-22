#ifndef SRC_MANIPULATOR_HPP_
#define SRC_MANIPULATOR_HPP_

#include <CANTalon.h>
#include <DigitalInput.h>
#include <Talon.h>


namespace FRC {

	class manipulator {
		public:
			manipulator();
			//Gear functions
			CANTalon gear;
			Talon ball, climbMotor;
			DigitalInput GearSwitch;
			PowerDistributionPanel PDP;

			//Gear Functions
			void GearReset(double speed);
			void GearOut(double speed);
			void ballEject();
			void climb();

		private:

	};
}



#endif




