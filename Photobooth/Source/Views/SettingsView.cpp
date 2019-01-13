#include "SettingsView.h"
#include <string> 
#include <algorithm>

SettingsView::SettingsView()
{
}


SettingsView::~SettingsView()
{
}

ViewDefinitions SettingsView::drawView()
{
	ViewDefinitions id = SettingsViewId;

	return id;
}

ViewDefinitions SettingsView::drawView(CameraSettings& settings)
{
	ViewDefinitions id = SettingsViewId;

	bool show_gui = true;
	ImGui::Begin("Settings", &show_gui, ImVec2(600, 1080), 0.0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDecoration);

	if (ImGui::Button("Fotobox Start", ImVec2(200, 100))) { id = StartViewId; };
	ImGui::SetCursorPosY(600);
	if (ImGui::Button("Close", ImVec2(200, 100))) { id = PhotoboothClose; };


	//ImGui::ShowTestWindow();

	ImGui::End();

	ImGui::Begin("Camera", &show_gui, ImVec2(600, 1080), 0.0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	{
        settings.update = true;

		std::string text = "FPS: " + std::to_string(settings.video_fps);
		ImGui::Text(text.c_str());
		text = "Width: " + std::to_string(settings.video_width);
		ImGui::Text(text.c_str());
		text = "Height: " + std::to_string(settings.video_height);
		ImGui::Text(text.c_str());
		std::string str(settings.video_format, settings.video_format + 4);
		text = "Format: " + str;
		ImGui::Text(text.c_str());
        
        ImGui::SliderInt("Brightness", (int*)&(settings.vi.Brightness.CurrentValue), settings.vi.Brightness.Min, settings.vi.Brightness.Max);
        //ImGui::SameLine();
        //static bool auto_set = false;
        //ImGui::Checkbox("Auto Brightness", &auto_set);
        //settings.vi.Brightness.Flag = auto_set * 1;
        ImGui::SliderInt("Contrast", (int*)&(settings.vi.Contrast.CurrentValue), settings.vi.Contrast.Min, settings.vi.Contrast.Max);
        ImGui::SliderInt("Hue", (int*)&(settings.vi.Hue.CurrentValue), settings.vi.Hue.Min, settings.vi.Hue.Max);
        ImGui::SliderInt("Saturation", (int*)&(settings.vi.Saturation.CurrentValue), settings.vi.Saturation.Min, settings.vi.Saturation.Max);
        ImGui::SliderInt("Gamma", (int*)&(settings.vi.Gamma.CurrentValue), settings.vi.Gamma.Min, settings.vi.Gamma.Max);
        ImGui::SliderInt("ColorEnable", (int*)&(settings.vi.ColorEnable.CurrentValue), settings.vi.ColorEnable.Min, settings.vi.ColorEnable.Max);
        ImGui::SliderInt("WhiteBalance", (int*)&(settings.vi.WhiteBalance.CurrentValue), settings.vi.WhiteBalance.Min, settings.vi.WhiteBalance.Max);
        ImGui::SliderInt("BacklightCompensation", (int*)&(settings.vi.BacklightCompensation.CurrentValue), settings.vi.BacklightCompensation.Min, settings.vi.BacklightCompensation.Max);
        ImGui::SliderInt("Gain", (int*)&(settings.vi.Gain.CurrentValue), settings.vi.Gain.Min, settings.vi.Gain.Max);
        ImGui::SliderInt("Pan", (int*)&(settings.vi.Pan.CurrentValue), settings.vi.Pan.Min, settings.vi.Pan.Max);
        ImGui::SliderInt("Tilt", (int*)&(settings.vi.Tilt.CurrentValue), settings.vi.Tilt.Min, settings.vi.Tilt.Max);
        ImGui::SliderInt("Roll", (int*)&(settings.vi.Roll.CurrentValue), settings.vi.Roll.Min, settings.vi.Roll.Max);
        ImGui::SliderInt("Zoom", (int*)&(settings.vi.Zoom.CurrentValue), settings.vi.Zoom.Min, settings.vi.Zoom.Max);
        ImGui::SliderInt("Exposure", (int*)&(settings.vi.Exposure.CurrentValue), settings.vi.Exposure.Min, settings.vi.Exposure.Max);
        ImGui::SliderInt("Iris", (int*)&(settings.vi.Iris.CurrentValue), settings.vi.Iris.Min, settings.vi.Iris.Max);
        ImGui::SliderInt("Focus", (int*)&(settings.vi.Focus.CurrentValue), settings.vi.Focus.Min, settings.vi.Focus.Max);

	}

	ImGui::End();

	return id;
}

void SettingsView::renderFPS(const std::vector<float>& time_stamps, const size_t& time_stamp) const
{
    bool show_gui = true;

    ImGui::Begin("Performance", &show_gui, ImVec2(600, 1080), 0.0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    {
        float time_min = 999999.9f;
        float time_max = -999999.9f;
        double total_time = 0.0;
        for (auto& t : time_stamps) {
            total_time += (double)t;
            time_min = std::min(time_min, t);
            time_max = std::max(time_max, t);
        }
        time_min -= time_min * 0.1f;
        time_max += time_max * 0.1f;
        
        total_time /= (double)time_stamps.size();
        double fps = 1.0 / (total_time / 1000.0);

        ImGui::PlotLines("ms", time_stamps.data(), time_stamps.size(), time_stamp % time_stamps.size(), ("FPS: " + std::to_string(fps)).c_str(), time_min, time_max, ImVec2(0, 80));
    }
    ImGui::End();
}
