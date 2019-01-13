#pragma once
#include "BaseView.h"
#include <CameraSettings.h>
#include <vector>

class SettingsView :
	public BaseView
{
	public:
		SettingsView();
		~SettingsView();

		ViewDefinitions drawView();
		ViewDefinitions drawView(CameraSettings&);
        void renderFPS(const std::vector<float>& time_stamps, const size_t& time_stamp) const;
        
	private:

};

