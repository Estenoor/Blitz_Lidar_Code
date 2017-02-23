/*
 * cameraManager.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: Robotics
 */
#include "WPILib.h"
#include "cameraManager.hpp"
#include "CameraServer.h"
#include "IterativeRobot.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/core/types.hpp"

void FRC::cameraManager::VisionThread()
{
	cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera("10.51.48.11");
	camera.SetResolution(640,480);
	camera.SetFPS(30);

	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("Rectangle", 640, 480);
	cv::Mat mat;

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
}

