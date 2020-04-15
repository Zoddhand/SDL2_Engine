#pragma once
#include "GameObject.h"
#include "Map.h"
class Player :
	public GameObject
{
private:
	enum{ Platformer, RPG };
	const Uint8* keys = SDL_GetKeyboardState(NULL);
public:
	static bool isOnGround;
	static int coins;

	Player(const char* texturesheet, float x, float y);
	void Movement(int);
	void PlatformerMove();
	void Collect(Map* map);
	virtual void update(Map* map);
	virtual void moveLeft(int style);
	virtual void moveRight(int style);
	virtual void moveUp();
	virtual void moveDown();
	void jump();
};

