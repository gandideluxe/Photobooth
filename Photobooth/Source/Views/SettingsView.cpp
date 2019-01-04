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
	ImGui::Begin("Settings", &show_gui, ImVec2(600, 400));

	if (ImGui::Button("Fotobox Start", ImVec2(200, 100))) { id = StartViewId; };
	bool m_close_application = ImGui::Button("Fotobox Ende", ImVec2(100, 100)); ImGui::SameLine();

	ImGui::ShowTestWindow();

	ImGui::End();

	return id;
}
