#include "OpenCVCameraGrab.h"
#include <fstream>


OpenCVCameraGrab::OpenCVCameraGrab()
{
}


OpenCVCameraGrab::~OpenCVCameraGrab()
{

}

unsigned OpenCVCameraGrab::get_camera_width()
{
	return m_video_width;
}

unsigned OpenCVCameraGrab::get_camera_height()
{
	return m_video_height;
}

int OpenCVCameraGrab::init()
{
	m_video_capture = cv::VideoCapture(0); // open the default camera
	if (!m_video_capture.isOpened())  // check if we succeeded
	{
		std::cerr << "Error openening Camera" << std::endl;
		std::cerr << "Generating Empty Image" << std::endl;

		m_video_width = 1024u;
		m_video_height = 720u;
		m_video_fps = 0.0;
		m_format = 0.0;

		m_frame_data.resize(m_video_width * m_video_height * 4);
		
		memset(m_frame_data.data(), 0xFF, m_frame_data.size() / 2);

		return -1;
	}
	else {
		double grabMode, frameFormat, settings;

		// Backed-specific value indicating the current capture mode.
		grabMode = m_video_capture.get(cv::CAP_PROP_MODE);
		// Format of the Mat objects returned by retrieve()
		frameFormat = m_video_capture.get(cv::CAP_PROP_FORMAT);
		// Some available settings 
		settings = m_video_capture.get(cv::CAP_PROP_SETTINGS);
		
#if 0
		// Playing around GRAB_MODE
		// Boolean flags indicating whether images should be converted to RGB.
		m_video_capture.set(cv::CAP_PROP_CONVERT_RGB, 0);
		int i = -100;
		while (ok == false && i < 10)
		{
			if (i != 0)
				ok = m_video_capture.set(cv::CAP_PROP_MODE, grabMode + i);
			i++;
		}
		if (ok)
		{
			grabMode = m_video_capture.get(cv::CAP_PROP_MODE);
			std::cout << "Grab Mode=" << grabMode << " is supported" << std::endl;
		}
#endif
		m_video_width = (unsigned)m_video_capture.get(cv::CAP_PROP_FRAME_WIDTH);
		m_video_height = (unsigned)m_video_capture.get(cv::CAP_PROP_FRAME_HEIGHT);
		m_video_fps = m_video_capture.get(cv::CAP_PROP_FPS);
		m_format = m_video_capture.get(cv::CAP_PROP_FORMAT);

		m_frame_data.resize(m_video_width * m_video_height * 4);
	}
	return 0;
}

void OpenCVCameraGrab::grab_image()
{	
	if (m_video_capture.isOpened()){
		cv::Mat cap;	
		//m_video_capture >> cap; // get a new frame from camera
		m_video_capture.read(cap);
		cv::cvtColor(cap, cap, cv::COLOR_BGR2RGBA);
		memcpy(m_frame_data.data(), (unsigned char*)(cap.data), m_frame_data.size());
#if 0
		std::ofstream file("image.raw", std::ios::out | std::ios::binary);
		file.write((char*)m_frame_data.data(), m_frame_data.size());
		//file.write((char*)cap.data, cap.rows * cap.cols);
		file.close();
#endif
	}
}

std::vector<unsigned char> OpenCVCameraGrab::get_image_data()
{	
	return m_frame_data;
}
