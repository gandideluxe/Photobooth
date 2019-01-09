#include "SettingsView.h"
#include <string> 

SettingsView::SettingsView()
{
}


SettingsView::~SettingsView()
{
}

ViewDefinitions SettingsView::drawView()
{
	ViewDefinitions id = SettingsViewId;

	bool show_gui = true;
	ImGui::Begin("Settings", &show_gui, ImVec2(600, 400), 0.0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDecoration);

	if (ImGui::Button("Fotobox Start", ImVec2(200, 100))) { id = StartViewId; };
	ImGui::SetCursorPosY(600);
	if (ImGui::Button("Close", ImVec2(200, 100))) { id = PhotoboothClose; };


	//ImGui::ShowTestWindow();

	ImGui::End();

	ImGui::SetCursorPos(ImVec2(400, 0));
	ImGui::Begin("Camera", &show_gui, ImVec2(500, 300), 0.2, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

	{
		// Using the _simplified_ one-liner Combo() api here
		// See "Combo" section for examples of how to use the more complete BeginCombo()/EndCombo() api.
		const char* items_fps[] = { "24Hz", "30Hz", "60Hz"};
		static int item_fps_current = 0;
		ImGui::Combo("FPS", &item_fps_current, items_fps, IM_ARRAYSIZE(items_fps));

		const char* items_res[] = { "800x600", "1920x1080", "60Hz" };
		static int item_res_current = 0;
		ImGui::Combo("Resolution", &item_res_current, items_fps, IM_ARRAYSIZE(items_res));
		
	}

	ImGui::End();

	return id;
}

ViewDefinitions SettingsView::drawView(CameraSettings settings)
{
	ViewDefinitions id = SettingsViewId;

	bool show_gui = true;
	ImGui::Begin("Settings", &show_gui, ImVec2(600, 400), 0.0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDecoration);

	if (ImGui::Button("Fotobox Start", ImVec2(200, 100))) { id = StartViewId; };
	ImGui::SetCursorPosY(600);
	if (ImGui::Button("Close", ImVec2(200, 100))) { id = PhotoboothClose; };


	//ImGui::ShowTestWindow();

	ImGui::End();

	//ImGui::SetCursorPos(ImVec2(400, 100));
	ImGui::Begin("Camera", &show_gui, ImVec2(500, 300), 0.2/*, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar*/);

	{
		std::string text = "FPS: " + std::to_string(settings.video_fps);
		ImGui::Text(text.c_str());
		text = "Width: " + std::to_string(settings.video_width);
		ImGui::Text(text.c_str());
		text = "Height: " + std::to_string(settings.video_height);
		ImGui::Text(text.c_str());
		std::string str(settings.video_format, settings.video_format + 4);
		text = "Format: " + str;
		ImGui::Text(text.c_str());

		// Using the _simplified_ one-liner Combo() api here
		// See "Combo" section for examples of how to use the more complete BeginCombo()/EndCombo() api.
		const char* items_fps[] = { "24Hz", "30Hz", "60Hz" };
		static int item_fps_current = 0;
		ImGui::Combo("FPS", &item_fps_current, items_fps, IM_ARRAYSIZE(items_fps));

		const char* items_res[] = { "800x600", "1920x1080", "60Hz" };
		static int item_res_current = 0;
		ImGui::Combo("Resolution", &item_res_current, items_fps, IM_ARRAYSIZE(items_res));
	}

	ImGui::End();

	return id;
}
