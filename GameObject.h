#pragma once
#include "Engine.h"

class GameObject
{
private:
	int tileSize;
	SDL_Texture* tex;
	struct Position
	{
		float x;
		float y;
	};

	struct Velocity
	{
		float x;  
		float y;  
		float speed = 20;
	};
	
	struct FrameManager
	{
		int offset_x;
		int offset_y;
		int num;
		SDL_RendererFlip flip;
	};

	int direction;
public:
	GameObject();
	GameObject(const char*, float, float);
	~GameObject();

	void update();
	void render();
	//void Movement(float);
	float* getXpos();
	float* getYpos();
	float* getXvel();
	float* getYvel();
	void setXpos(float y);
	void setYpos(float y);
	void setXvel(float vel);
	void setYvel(float vel);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	// Public Variables Because i'm trash.
	SDL_Rect dest = { 0, 0, tileSize, tileSize };
	SDL_Rect src = { 0, 0, tileSize, tileSize };

	Position pos = { 0, 0 };
	Velocity vel = { 0.0f, 0.0f };
	FrameManager frame = { 0, 0, 1, SDL_FLIP_NONE };
};

