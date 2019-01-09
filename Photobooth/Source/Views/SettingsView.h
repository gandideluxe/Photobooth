#pragma once
#include "BaseView.h"
#include <CameraSettings.h>

class SettingsView :
	public BaseView
{
	public:
		SettingsView();
		~SettingsView();

		ViewDefinitions drawView();
		ViewDefinitions drawView(CameraSettings);

	private:
		bool show_test_window = true;
};

