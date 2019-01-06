#include "FinishView.h"

FinishView::FinishView()
{
}


FinishView::~FinishView()
{
}

ViewDefinitions FinishView::drawView()
{
	ViewDefinitions id = FinishViewId;

	bool show_gui = true;
	ImGui::Begin("Finish", &show_gui, ImVec2(600, 400), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDecoration);

	bool m_fotobox_start = ImGui::Button("Fotobox Start", ImVec2(100, 100)); ImGui::SameLine();
	bool m_open_settings = ImGui::Button("Fotobox Settings", ImVec2(100, 100)); ImGui::SameLine();;
	bool m_close_application = ImGui::Button("Fotobox Ende", ImVec2(100, 100)); ImGui::SameLine();

	ImGui::End();

	return id;
}
