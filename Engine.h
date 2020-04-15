#pragma once
#define print(x) std::cout << x << std::endl;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


class Engine
{
private:
	//Sound Variables Set enum to sound effect ie. jump.
	Mix_Music* Bg = NULL;
	Mix_Chunk* effect[10];
	enum{ E1, E2 };

public:
	Engine(const char* , int , int , bool);
	~Engine();
	//Public Variables.
	bool run = true;

	//Static Variables.
	static SDL_Window* window;
	static SDL_Event event;
	static SDL_Renderer* renderer;
	static const int tileSize = 8;
	static const int screen_width = 128;
	static const int screen_height = 120;
	static const int mapSizeX = 80;
	static const int mapSizeY = 30;
	static float time;

	//Static Functions.

	//Functions.
	void handle_event(float);
	void update();
	void render();
	void playBG();
};

