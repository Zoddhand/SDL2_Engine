#pragma once
#include "Engine.h"

class Camera
{
private:


public:
	Camera();
	~Camera();
	struct Rect
	{
		int x;
		int y;
		int w;
		int h;
	};

	static float offX;
	static float offY; 
	static Rect cam;
	static Rect vis;

	float getoffX();
	float getoffY();
	static void update(float, float);
};
