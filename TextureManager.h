#pragma once
#include "Engine.h"
#include "SDL_ttf.h"

class TextureManager
{
public:
	TextureManager();
	static SDL_Texture* loadTexture(const char* filename, bool message = 1);
	static void Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip = SDL_FLIP_NONE);
	static void DrawRect(SDL_Rect dest);
	static void FrameUpdate(SDL_Rect* src, int framenum, int x, int y);
	static TTF_Font* LoadFont(const char* file, int ptsize);
	static void DrawFont(TTF_Font* font, const char* mess, SDL_Color textColor, SDL_Rect dest);
private:
	SDL_RendererFlip flip;

};

