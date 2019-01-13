#pragma once
#include <videoInput.h>

class CameraSettings
{
public:
	CameraSettings();
	~CameraSettings();

	double			video_fps = 0.0;
	unsigned		video_width = 0u;
	unsigned		video_height = 0u;
	unsigned char	video_format[4];

    CamParametrs    vi;
    bool            update;
};

