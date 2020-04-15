// SDL2_Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Engine.h"
#include <chrono>

Engine* engine = nullptr;

const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frametime = 0;

int main(int argc, char* argv[])
{
	engine = new Engine("Death's Door", 500, 50, false);

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (engine->run)
	{
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;

		// Our time per frame coefficient
		float fElapsedTime = elapsedTime.count();

		frameStart = SDL_GetTicks();
		Engine::time = fElapsedTime;
		engine->handle_event(fElapsedTime);
		engine->update();
		engine->render();

		frametime = SDL_GetTicks() - frameStart;

		if (frameDelay > frametime)
		{
			SDL_Delay(frameDelay - frametime);
			//system("CLS");
		}
	}
	return 0;
}
