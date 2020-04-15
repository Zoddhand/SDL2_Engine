#include "Engine.h"
#include <iostream>
using namespace std;
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Camera.h"
#include "Player.h"
#include "Collision.h"
#include "Sound.h"

float Engine::time;

SDL_Window* Engine::window = nullptr;
SDL_Renderer* Engine::renderer = nullptr;
SDL_Event Engine::event;
Camera* camera = nullptr;
Map* map = nullptr;
Player* player = nullptr;
Collision* col = nullptr;
Sound* sound = nullptr;



Engine::Engine(const char* title, int posX, int posY, bool fullscreen)
{
	int scale = 3.0f;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		print("Error: SDL NOT INITIALIZED -" << SDL_GetError())
	}
	else print("Subsystems Started");

	window = SDL_CreateWindow(title, posX, posY, screen_width, screen_height, fullscreen);
	if (window == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Window did not Create.", NULL);
	}
	SDL_SetWindowSize(window, screen_width * scale, screen_height * scale);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Renderer did not Create.", NULL);
	}
	SDL_RenderSetScale(renderer, scale, scale);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	Bg = Sound::loadBackground("Assets/Sound/BG.wav");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		print("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	camera = new Camera();
	map = new Map();
	player = new Player("Assets/Sprites/hero.png", 10, 10);
	col = new Collision(map);
	sound = new Sound();
}

Engine::~Engine()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete camera;
	delete map;
	delete player;
	delete col;
	delete sound;
	SDL_Quit();
}

void Engine::handle_event(float time)
{
	/* gets items in the event queue */
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		print("SDL Successfully Quit!");
		break;
	}

	/* Get key presses */
	if (Engine::event.type == SDL_KEYDOWN)
	{
		switch (Engine::event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			run = false;
			break;
		}
	}
	
	player->Movement();
}

void Engine::update()
{
	playBG();
	col->collide(*player->getXpos(), *player->getYpos(), *player->getXvel(), *player->getYvel());
	player->update(map);
	camera->update(*player->getXpos(), *player->getYpos());
	map->update();
}

void Engine::render()
{
	SDL_RenderClear(renderer);
	map->render();
	player->render();
	SDL_RenderPresent(renderer);
}

void Engine::playBG()
{
	Sound::setVolume(50);
	Sound::playBackground(Bg,1);
}