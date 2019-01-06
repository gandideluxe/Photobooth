#include "FotoboothView.h"

FotoboothView::FotoboothView()
{
}

FotoboothView::~FotoboothView()
{
}

ViewDefinitions FotoboothView::drawView()
{
	ViewDefinitions id = PhotoboothViewId;

	bool show_gui = true;
	ImGui::Begin("Photobox", &show_gui, ImVec2(600, 400), 0.0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDecoration);

	if (ImGui::Button("Start View", ImVec2(200, 100))) { id = StartViewId; };

	ImGui::End();

	return id;
}
