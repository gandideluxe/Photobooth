#pragma once
#include "BaseView.h"

class StartView :
	public BaseView
{
	public:
		StartView();
		~StartView();

		ViewDefinitions drawView();
	
};

