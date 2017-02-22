
#ifndef SRC_DRIVEMANAGER_HPP_
#define SRC_DRIVEMANAGER_HPP_

#include <inputManager.hpp>
#include <wpilib.h>
#include <CanTalon.h>
#include "AHRS.h"
namespace FRC {

	class driveManager {
		public:
		//Declare Objects
		driveManager();
		CANTalon leftBackM, leftFrontM, rightBackM, rightFrontM; //enc: 3024 counts / 1 rev
		AHRS ahrs;
		FRC::inputManager inputManager;
		//Declare Functions
		void PIcorrection(int id);
		void mecanumDrive(double x, double y, double rotate, bool bypass);
		void ramp();
		void straightDrive(double PreAngle);
		double getEncDistance();
		void resetEnc();
		void driveDistance(double distance);
		void rotate(double degrees);
		//void autoTurn(float angle)
		int getAngle();
		//JoySticks
		double JoyX;
		double JoyY;
		double joyRotate;
		double JoyXRaw;
		double JoyYRaw;
		double JoyRotateRaw;

		//straight Drive
		double speeds[4];
		double Angle;
		double zachG;
		double rotation;
		double mrKrack = .075;
		double delta = 0;
		double Multiplier[4];
		int dir = 1;

		//PIcorrection
		double EncoderFreq[4];
		double spdRef[4];
		double SPFeedBack[4];
		double error[4];
		double intOut[4];
		double propOut[4];
		double PIout[4];
		double PWMout[4];
		bool intReset = false;
		private:
	};
}




#endif




