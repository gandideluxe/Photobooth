#include "SettingsView.h"

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


	ImGui::ShowTestWindow();

	ImGui::End();

	return id;
}
