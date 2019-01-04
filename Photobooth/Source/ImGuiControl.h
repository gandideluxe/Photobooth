#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

class ImGuiControl
{
	public:
		ImGuiControl() {};
		~ImGuiControl() {};

		int init(GLFWwindow* window, const char* glsl_version);
		int startFrame();
		int endFrame();
		int renderDrawData();
		int cleanup();
};

