#pragma once
#include "Engine.h"
#include <string>
#include "Camera.h"
#include "TextureManager.h"

class Map
{
private:
	struct Spr
	{
		SDL_Texture* tex = nullptr;
		SDL_Rect src = { 0,0,16,16 };
		SDL_Rect dest = { 0,0,16,16 };
		int framenum = 1;
	};
	Spr sprite[10];
	int count = 0;
	enum Sprite_name { tile, background, bomb, explosion, coin };

	int maps[Engine::mapSizeY][Engine::mapSizeX];
	int maps2[Engine::mapSizeY][Engine::mapSizeX];
	int mapsCol[Engine::mapSizeY][Engine::mapSizeX];
	int mapsItem[Engine::mapSizeY][Engine::mapSizeX];

	int imagew;
	int imageh;
	int tilesize;
public:
	Map();
	~Map();

	void update();
	void render();
	void loadMap(std::string txt, int arr[Engine::mapSizeY][Engine::mapSizeX]);
	void drawMap(int arr[Engine::mapSizeY][Engine::mapSizeX]);
	void drawBackground();
	void loadLevel(int level);

	int getColTile(float x, float y);
	void setColTile(float x, float y, int value);
	int getItemTile(float x, float y);
	void setItemTile(float x, float y, int value);
};

