#pragma once
#include <opencv2/opencv.hpp>

class OpenCVCameraGrab
{
public:
	OpenCVCameraGrab();
	~OpenCVCameraGrab();

	unsigned get_camera_width();
	unsigned get_camera_height();

	int init();
	void grab_image();
	std::vector<unsigned char> get_image_data();
	
private:
	cv::VideoCapture m_video_capture;
	std::vector<unsigned char> m_frame_data;

	unsigned m_video_width = 0;
	unsigned m_video_height = 0;
	double m_video_fps = 0.0;
	double m_format = 0.0;

};

