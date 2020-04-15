#include "Collision.h"
#include "Map.h"
#include <iostream>
#include "Player.h"

Collision::Collision(Map* m)
{
	map = m;
}

/* Test Collision with the tilemap and adjust the player accordingly. */
void Collision::collide(float& x, float& y,float& velx, float& vely)
{
	float nposX = x + velx * Engine::time;
	float nposY = y + vely * Engine::time;

	if (velx <= 0)
	{
		if (map->getColTile(nposX + 0.0f, y + 0.0f) != -1 || map->getColTile(nposX + 0.0f, y + 0.9f) != -1)
		{
			nposX = (int)nposX + 1;
			velx = 0;
		}
	}
	else
	{
		if (map->getColTile(nposX + 1.0f, y + 0.99f) != -1 || map->getColTile(nposX + 1.0f, y + 0.9f) != -1)
		{
			nposX = (int)nposX;
			velx = 0;
		}
	}
	if (vely <= 0)
	{
		if (map->getColTile(nposX + 0.0f, nposY) != -1 || map->getColTile(nposX + 0.9f, nposY) != -1)
		{
			nposY = (int)nposY + 1;
			vely = 0;
		}
	}
	else
	{
		if (map->getColTile(nposX + 0.0f, nposY + 1.0f) != -1 || map->getColTile(nposX + 0.9f, nposY + 1.0f) != -1)
		{
			nposY = (int)nposY;
			vely = 0;
		}
	}
	if (map->getColTile(x + 0.0f, y + 1.0f) != -1 || map->getColTile(x + 0.9f, y + 1.0f) != -1)
	{
		Player::isOnGround = true;
	}
	else
		Player::isOnGround = false;

	x = nposX;
	y = nposY;
}

/* Test if 2 Rects are Touching */
bool Collision::rectCol(SDL_Rect p, SDL_Rect e)
{
	if (p.x < e.x + e.w &&
		p.x + p.w >  e.x &&
		p.y < e.y + e.h &&
		p.y + p.h > e.y)
	{
		return true;
	}
	else return false;
}

/* Used to collect items. It may be smarter to make this static in map.h */
bool Collision::ItemCollect(Map* map, int x, int y, int tile, int newTile)
{
	if (map->getItemTile(x + 0.0f, y + 0.0f) == tile)
	{
		if (newTile != -1)
		{
			map->setItemTile(x + 0.0f, y + 0.0f, newTile);
		}
		return true;
	}
	if (map->getItemTile(x + 0.0f, y + 1.0f) == tile)
	{
		if (newTile != -1)
		{
			map->setItemTile(x + 0.0f, y + 1.0f, newTile);
		}
		return true;
	}
	if (map->getItemTile(x + 1.0f, y + 0.0f) == tile)
	{
		if (newTile != -1)
		{
			map->setItemTile(x + 1.0f, y + 0.0f, newTile);
		}
		return true;
	}
	if (map->getItemTile(x + 1.0f, y + 1.0f) == tile)
	{
		if (newTile != -1)
		{
			map->setItemTile(x + 1.0f, y + 1.0f, newTile);
		}
		return true;
	}
	return false;
}