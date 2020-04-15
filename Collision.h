#pragma once
#include "Engine.h"
#include "Map.h"

class Collision
{
private:
	Map* map;
public:
	Collision(Map*);
	void collide(float& x, float& y,float& velx, float& vely);
	static bool rectCol(SDL_Rect p, SDL_Rect e);
	static bool ItemCollect(Map* map, int x, int y, int tile, int newTile);
};

