#include "StartView.h"

StartView::StartView()
{
}



StartView::~StartView()
{
}

ViewDefinitions StartView::drawView()
{
	ViewDefinitions id = StartViewId;
		
	bool show_gui = true;
	ImGui::Begin("Welcome", &show_gui, ImVec2(600, 400), 0.0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDecoration);
	
	if (ImGui::Button("Start", ImVec2(200, 100))) { id = PhotoboothViewId; };
	ImGui::SetCursorPosY(300);
	if (ImGui::Button("Settings", ImVec2(200, 100))) { id = SettingsViewId; };
	ImGui::SetCursorPosY(600);
	if (ImGui::Button("Close", ImVec2(200, 100))) { id = PhotoboothClose; };

	ImGui::End();

	return id;
}
