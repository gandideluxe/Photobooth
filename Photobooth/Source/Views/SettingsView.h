#pragma once
#include "BaseView.h"

class SettingsView :
	public BaseView
{
	public:
		SettingsView();
		~SettingsView();

		ViewDefinitions drawView();

	private:
		bool show_test_window = true;
};

