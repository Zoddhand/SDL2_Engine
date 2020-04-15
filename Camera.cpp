#include "Camera.h"

float Camera::offX;
float Camera::offY;
Camera::Rect Camera::cam;
Camera::Rect Camera::vis;

Camera::Camera()
{
	offX = 0;
	offY = 0;
	cam = { 0, 0, Engine::screen_width , Engine::screen_height };
	vis = { Engine::screen_width / Engine::tileSize, Engine::screen_height / Engine::tileSize,Engine::tileSize,Engine::tileSize };
}

Camera::~Camera()
{

}

/* Controlls the camera. Takes in player x and y */
void Camera::update(float Px, float Py)
{
	cam.x = Px;
	cam.y = Py;

	offX = Px - (float)vis.x / 2.0f;
	offY = Py - (float)vis.y / 2.0f;

	//Keep the camera in bounds
	if (offX < 0)
	{
		offX = 0;
	}
	if (offY < 0)
	{
		offY = 0;
	}

	if (offX > Engine::mapSizeX - vis.x)
	{
		offX = Engine::mapSizeX - vis.x;
	}
	if (offY > Engine::mapSizeY - vis.y)
	{
		offY = Engine::mapSizeY - vis.y;
	}

}

float Camera::getoffX()
{
	return offX;
}
float Camera::getoffY()
{
	return offY;
}