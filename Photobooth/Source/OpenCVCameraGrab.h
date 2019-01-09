#pragma once
#include <opencv2/opencv.hpp>
#include <CameraSettings.h>


class OpenCVCameraGrab
{
public:
	OpenCVCameraGrab();
	~OpenCVCameraGrab();

	void update_camera_settings();
	void set_camera_settings(CameraSettings);
	CameraSettings get_camera_settings();
	
	int init();
	void grab_image();
	std::vector<unsigned char> get_image_data();
	
private:
	cv::VideoCapture m_video_capture;
	std::vector<unsigned char> m_frame_data;
		
	CameraSettings m_camera_settings;

};

