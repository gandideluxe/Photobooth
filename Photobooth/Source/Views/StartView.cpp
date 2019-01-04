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
	ImGui::Begin("Control", &show_gui, ImVec2(600, 400));
	
	if (ImGui::Button("Photobox Settings", ImVec2(200, 100))) { id = SettingsViewId; };
	if (ImGui::Button("Photobox Start", ImVec2(200, 100))) { id = PhotoboothViewId; };
	
	
	bool m_close_application = ImGui::Button("Photobox Ende", ImVec2(200, 100));


	ImGui::End();

	return id;
}
