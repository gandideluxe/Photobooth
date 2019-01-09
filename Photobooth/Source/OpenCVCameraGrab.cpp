#include "OpenCVCameraGrab.h"
#include <fstream>


OpenCVCameraGrab::OpenCVCameraGrab()
{
}


OpenCVCameraGrab::~OpenCVCameraGrab()
{

}

void OpenCVCameraGrab::update_camera_settings()
{
	m_camera_settings.video_width = (unsigned)m_video_capture.get(cv::CAP_PROP_FRAME_WIDTH);
	m_camera_settings.video_height = (unsigned)m_video_capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	m_camera_settings.video_fps = m_video_capture.get(cv::CAP_PROP_FPS);

	int codec = m_video_capture.get(cv::CAP_PROP_FOURCC);
	for (int i = 0; i != 4; ++i) {
		m_camera_settings.video_format[i] = ((unsigned char*)&codec)[i];
	}
}

void OpenCVCameraGrab::set_camera_settings(CameraSettings settings)
{
	m_video_capture.set(cv::CAP_PROP_FRAME_WIDTH, settings.video_width);
	m_video_capture.set(cv::CAP_PROP_FRAME_HEIGHT, settings.video_height);
	m_video_capture.set(cv::CAP_PROP_FPS, settings.video_fps);
	int codec = cv::VideoWriter::fourcc(settings.video_format[0], settings.video_format[1], settings.video_format[2], settings.video_format[3]);
	m_video_capture.set(cv::CAP_PROP_FOURCC, codec);	
}

CameraSettings OpenCVCameraGrab::get_camera_settings()
{
	return m_camera_settings;
}

int OpenCVCameraGrab::init()
{
	m_video_capture = cv::VideoCapture(1); // open the default camera
	if (!m_video_capture.isOpened())  // check if we succeeded
	{		
		std::cerr << "Error openening Camera" << std::endl;
		std::cerr << "Generating Empty Image" << std::endl;

		m_camera_settings.video_width = 1024u;
		m_camera_settings.video_height = 720u;
		m_camera_settings.video_fps = 0.0;

		m_frame_data.resize(m_camera_settings.video_width * m_camera_settings.video_height * 3);
		
		memset(m_frame_data.data(), 0xFF, m_frame_data.size() / 2);

		return -1;
	}
	else {
		//int codec = cv::VideoWriter::fourcc('Y', 'U', 'Y', '2');
		//m_video_capture.set(cv::CAP_PROP_FOURCC, codec);

		update_camera_settings();

		m_frame_data.resize(m_camera_settings.video_width * m_camera_settings.video_height * 3);
	}
	return 0;
}

void OpenCVCameraGrab::grab_image()
{	
	if (m_video_capture.isOpened()){
		cv::Mat cap;	
		//m_video_capture >> cap; // get a new frame from camera
		bool success = m_video_capture.read(cap);
		//cv::cvtColor(cap, cap, cv::COLOR_BGR2RGBA);
		if(success)
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
