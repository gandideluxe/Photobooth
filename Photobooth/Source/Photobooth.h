#pragma once

#include <ImGuiControl.h>
#include <stdio.h>
#include <memory>
#include <vector>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h> 

#include <ViewDefinitions.h>
#include <Views\BaseView.h>
#include <Views\StartView.h>
#include <Views\FotoboothView.h>
#include <Views\FinishView.h>
#include <Views\SettingsView.h>

#include <OpenCVCameraGrab.h>
#include <MediaFoundationCameraGrab.h>

#include <plane.hpp>

class Photobooth
{
public:
	Photobooth();
	~Photobooth();

	int init();
	int render_image();
	int start();

private:

	GLFWwindow* m_window;
	ImGuiControl m_imgui_control;

	std::vector<std::shared_ptr<BaseView>> view_container;
	ViewDefinitions m_current_view = ViewDefinitions::StartViewId;

    //OpenCVCameraGrab m_camera_grabber;
    MediaFoundationCameraGrab m_camera_grabber;
	
	std::shared_ptr<Plane> m_plane = nullptr;
	GLuint m_image_texture = 0;

	std::string m_vertex_shader = ".//Source//shader//plane.vert";
	std::string m_fragment_shader = ".//Source//shader//plane.frag";
	GLuint m_fotobooth_program = 0;
	std::string m_error_message = "";

	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

};

