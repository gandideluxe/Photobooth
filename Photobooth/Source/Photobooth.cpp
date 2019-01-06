#include "Photobooth.h"
#include <utils.hpp>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/norm.hpp>

Photobooth::Photobooth()
{
}


Photobooth::~Photobooth()
{
}

int Photobooth::init()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	// Create window with graphics context
	m_window = glfwCreateWindow(1280, 720, "Photobooth", NULL, NULL);
	if (m_window == NULL)
		return 1;
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1); // Enable vsync

	bool err = gl3wInit() != 0;

	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}
		
	m_imgui_control.init(m_window, glsl_version);

	//Take care of order defined in ViewDefinitons.h
	view_container.push_back(std::shared_ptr<StartView>(new StartView()));
	view_container.push_back(std::shared_ptr<SettingsView>(new SettingsView()));
	view_container.push_back(std::shared_ptr<FotoboothView>(new FotoboothView()));
	view_container.push_back(std::shared_ptr<FinishView>(new FinishView()));

	m_camera_grabber.init();
	m_camera_grabber.grab_image();
	auto image_data = m_camera_grabber.get_image_data();
	glActiveTexture(GL_TEXTURE1);
	m_image_texture = createTexture2D(m_camera_grabber.get_camera_width(), m_camera_grabber.get_camera_height(), (char*)image_data.data());

	GLuint newProgram(0);
	try {
		//std::cout << "Reload shaders" << std::endl;
		newProgram = createProgram(readFile(m_vertex_shader), readFile(m_fragment_shader));
		m_error_message = "";
	}
	catch (std::logic_error& e) {
		std::cout << e.what() << std::endl;
		std::stringstream ss;
		ss << e.what() << std::endl;
		m_error_message = ss.str();
		newProgram = 0;
	}
	if (0 != newProgram) {
		glDeleteProgram(m_fotobooth_program);
		m_fotobooth_program = newProgram;
	}

	m_plane = std::shared_ptr<Plane>(new Plane());

	return 0;
}

int Photobooth::render_image() {
	//Update Image + Rendering
	m_camera_grabber.grab_image();
	auto data = m_camera_grabber.get_image_data();
	updateTexture2D(m_image_texture, m_camera_grabber.get_camera_width(), m_camera_grabber.get_camera_height(), (char*)data.data());
	

	const float ortho_projection[4][4] =
	{
		{ 2.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, -2.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, -1.0f, 0.0f },
		{ -1.0f, 1.0f, 0.0f, 1.0f },
	};
	glm::mat4 view = glm::mat4(1.0);

	//glViewport(tf_pos.x, tf_pos.y, (int)tf_size.x, (int)tf_size.y);

	glUseProgram(m_fotobooth_program);
	glUniformMatrix4fv(glGetUniformLocation(m_fotobooth_program, "Projection"), 1, GL_FALSE,
		//glm::value_ptr(projection));
		&ortho_projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(m_fotobooth_program, "Modelview"), 1, GL_FALSE,
		glm::value_ptr(view));

	// set texture uniform
	glUniform1i(glGetUniformLocation(m_fotobooth_program, "image_texture"), 1);

	m_plane->draw();

	glUseProgram(0);

	return 0;
}


int Photobooth::start()
{
	
	// Main loop
	while (!glfwWindowShouldClose(m_window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		int display_w, display_h;
		glfwMakeContextCurrent(m_window);
		glfwGetFramebufferSize(m_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		m_imgui_control.startFrame();
				
		if (m_current_view == ViewDefinitions::StartViewId) {
			m_current_view = std::static_pointer_cast<StartView>(view_container[StartViewId])->drawView();
		}
		if (m_current_view == ViewDefinitions::SettingsViewId) {		
			m_current_view = std::static_pointer_cast<SettingsView>(view_container[SettingsViewId])->drawView();
		}
		if (m_current_view == ViewDefinitions::PhotoboothViewId) {
			m_current_view = std::static_pointer_cast<FotoboothView>(view_container[PhotoboothViewId])->drawView();
			

			//glViewport(200, 0, display_w, display_h);
		}
		//if (current_view->get_id() == 2) {
		//	current_view = settings_view;
		//	((SettingsView*)current_view)->drawView();
		//}
		
		if (m_current_view == ViewDefinitions::PhotoboothClose) {
			glfwSetWindowShouldClose(m_window, true);
		}
		

		
		m_imgui_control.endFrame();
		render_image();
		
		m_imgui_control.renderDrawData();

		glfwSwapBuffers(m_window);
		glfwPollEvents();

	}

	m_imgui_control.cleanup();
	// Cleanup
	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}
