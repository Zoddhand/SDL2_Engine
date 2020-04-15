#pragma once
#include "GameObject.h"
#include "Map.h"
class Player :
	public GameObject
{
private:
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);
public:
	static bool isOnGround;
	Player(const char* texturesheet, float x, float y);
	void Movement();
	void PlatformerMove();
	void Collect(Map* map);
	virtual void update(Map* map);
	virtual void moveLeft();
	virtual void moveRight();
	virtual void moveUp();
	virtual void moveDown();
};

