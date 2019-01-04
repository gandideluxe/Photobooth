#pragma once
#include <imgui.h>
#include <ViewDefinitions.h>

class BaseView
{
public:
	BaseView();
	~BaseView();

	virtual ViewDefinitions drawView();

};

