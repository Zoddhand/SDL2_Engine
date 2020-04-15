#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>

Map::Map()
{
	tilesize = Engine::tileSize;

	/* Tile Init */
	sprite[tile].tex = TextureManager::loadTexture("Assets/tiles/tile_example.png");
	sprite[tile].src = { 0,0,Engine::tileSize,Engine::tileSize };
	sprite[tile].dest = { 0,0,Engine::tileSize,Engine::tileSize };
	SDL_QueryTexture(sprite[tile].tex, NULL, NULL, &imagew, &imageh);
	sprite[tile].dest.w = Engine::tileSize;
	sprite[tile].dest.h = Engine::tileSize;
	imagew = imagew / tilesize;
	imageh = imageh / tilesize;

	/* Coin Init */
	sprite[coin].tex = TextureManager::loadTexture("Assets/sprites/Red_coin.png");

	loadLevel(1);
}

Map::~Map()
{

}

void Map::update()
{
}

void Map::render()
{
	drawMap(maps2);
	drawMap(maps);
	//drawMap(mapsCol);
	drawMap(mapsItem);
}

void Map::loadMap(std::string txt, int arr[Engine::mapSizeY][Engine::mapSizeX])
{
	std::fstream fs(txt, std::fstream::in | std::fstream::out);
	if (fs.is_open()) {
		while (!fs.eof()) {
			if (fs.get() == ',') {
				fs.seekp((fs.tellp() - static_cast<std::streampos>(1)));
				fs.put(' ');
				fs.seekp(fs.tellp());
			}
		}
	}
	else
	{
		print("Unable to fix file:" << txt);
		fs.close();
	}

	std::ifstream map;
	map.open(txt);

	if (!map) {
		print("Unable to open file:" << txt);
		exit(1);
	}
	else print("File:" << txt << " Opened Successfully");

	if (map.is_open())
	{
		while (!map.eof())
		{
			for (int i = 0; i < Engine::mapSizeY; ++i) {
				for (int j = 0; j < Engine::mapSizeX; ++j) {
					map >> arr[i][j];
					//cout << arr[i][j];
				}
				//cout << endl;
			}
		}
	}
	map.close();
}

void Map::drawMap(int arr[Engine::mapSizeY][Engine::mapSizeX])
{
	for (int i = 0; i < Camera::vis.y + Camera::offY; i++)
	{
		for (int k = 0; k < Camera::vis.x + Camera::offX; k++)
		{
			sprite[tile].src.y = (arr[i][k] / imagew) * Engine::tileSize;
			sprite[tile].src.x = (arr[i][k] % imagew) * Engine::tileSize;
			sprite[tile].dest.x = (k - Camera::offX) * Engine::tileSize;
			sprite[tile].dest.y = (i - Camera::offY) * Engine::tileSize;
			if (arr[i][k] != -1)
			{
				TextureManager::Draw(sprite[tile].tex, sprite[tile].src, sprite[tile].dest);
			}
			if (arr[i][k] == 12)
			{
				sprite[coin].dest.x = sprite[tile].dest.x;
				sprite[coin].dest.y = sprite[tile].dest.y;
				sprite[coin].dest.w = 8;
				sprite[coin].dest.h = 8;
				TextureManager::Draw(sprite[coin].tex, sprite[coin].src, sprite[coin].dest);
				TextureManager::FrameUpdate(&sprite[coin].src, 14, 0, 0);
			}
		}
	}
}

/* Sends the correct file to the loadMap function. */
void Map::loadLevel(int level)
{
	// Create a new string to add levels.
	std::string* ptr = nullptr;
	std::string map1[4] = { "Assets/Maps/tiled_example_Tile Layer 1.csv","Assets/Maps/tiled_example_Tile Layer 2.csv","Assets/Maps/tiled_example_Col Layer.csv","Assets/Maps/tiled_example_Item Layer.csv" };
	std::string map2[4] = { "Assets/Maps/tiled_example2_Tile Layer 1.csv","Assets/Maps/tiled_example2_Tile Layer 2.csv","Assets/Maps/tiled_example2_Col Layer.csv","Assets/Maps/tiled_example2_Item Layer.csv" };

	switch (level)
	{
	case 1: // level 1
		ptr = map1;
		break;
	case 2:
		ptr = map2;
		break;
	case 3:
		//ptr = map3;
		break;
	default:
		ptr = map1;
	}
	print("level:" << level << " loaded.");

	// Send all our layers for the level we've chosen to be loaded into the map array.
	loadMap(ptr[0], maps); // Our first map to load.
	loadMap(ptr[1], maps2); // Our second map to load.
	loadMap(ptr[2], mapsCol); // Our third map to load.
	loadMap(ptr[3], mapsItem); // Our third map to load.
}

void Map::drawBackground()
{
}

int Map::getColTile(float x, float y)
{
	return mapsCol[(int)y][(int)x];
}

void Map::setColTile(float x, float y, int value)
{
	mapsCol[(int)y][(int)x] = value;
}

int Map::getItemTile(float x, float y)
{
	return mapsItem[(int)y][(int)x];
}

void Map::setItemTile(float x, float y, int value)
{
	mapsItem[(int)y][(int)x] = value;
}

