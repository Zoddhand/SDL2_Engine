#include "Engine.h"
#include <SDL_ttf.h>
#include "TextureManager.h"
#include "Player.h"
#include <iostream>
#include <string>

void Engine::hud()
{
	TTF_Font* font;
	SDL_Rect dest = { 0, 0, 32, 8 };
	dest.y = screen_height - dest.h;
	font = TextureManager::LoadFont("Assets/Fonts/Example_font.ttf",16);

	//Text Example. Create a string then add our variable to it.
	std::string text = "Coins: ";
	text += std::to_string(Player::coins);
	const char* c = text.c_str();
	TextureManager::DrawFont(font, c, { 255,255,50}, dest);
}