#include "ImGuiControl.h"

int ImGuiControl::init(GLFWwindow* window, const char* glsl_version) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGuiStyle * style = &ImGui::GetStyle();
	style->WindowBorderSize = 0.0f;

	ImGuiIO& io = ImGui::GetIO();
	
	//io.Fonts->AddFontFromFileTTF((".\\Fonts\\Ruda\\Ruda-Bold.ttf"), 10);
	//io.Fonts->AddFontFromFileTTF((".\\Fonts\\Ruda\\Ruda-Bold.ttf"), 12);
	//io.Fonts->AddFontFromFileTTF((".\\Fonts\\Ruda\\Ruda-Bold.ttf"), 14);
	io.Fonts->AddFontFromFileTTF((".\\Fonts\\Ruda\\Ruda-Bold.ttf"), 32);

	return 0;
}

int ImGuiControl::startFrame() {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	return 0;

}

int ImGuiControl::endFrame() {
	ImGui::Render();

	return 0;

};

int ImGuiControl::renderDrawData() {
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	return 0;

};

int ImGuiControl::cleanup() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;

};