#pragma once
#include "Engine.h"
#include <iostream>

class Sound
{
public:
	Sound()
	{

	}
	static Mix_Music* loadBackground(const char* file)
	{
		Mix_Music* gMusic = NULL;

		//Load music
		gMusic = Mix_LoadMUS(file);
		if (gMusic == NULL)
		{
			print("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		}
		else
		{
			print("Music File Loaded Successfully:" << file);
		}
		//Mix_FreeMusic(gMusic);

		//Load sound effects
		return gMusic;
	}

	/* State 1 plays music. state 2 pauses/resumes music. state 3 stop music.*/
	static void playBackground(Mix_Music* gMusic, int state)
	{
		switch (state)
		{
		case 1:
			if (Mix_PlayingMusic() == 0)
			{
				//Play the music
				Mix_PlayMusic(gMusic, -1);
			}
			break;
		case 2:
			if (Mix_PlayingMusic() != 0)
			{
				if (Mix_PausedMusic() == 1)
				{
					Mix_ResumeMusic();
				}
				else
					Mix_PauseMusic();
			}
			break;
		case 3:
			Mix_HaltMusic();
			break;
		}
	}

	static Mix_Chunk* loadEffect(const char* file)
	{
		Mix_Chunk* effect = NULL;
		effect = Mix_LoadWAV(file);
		if (effect == NULL)
		{
			print("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		}
		return effect;
	}
	static void playEffect(Mix_Chunk* sound)
	{
		Mix_PlayChannel(-1, sound, 0);
	}
	/* Volume 0-128 */
	static void setVolume(int vol, Mix_Chunk* e = NULL)
	{
		Mix_VolumeMusic(vol);
		if (e != NULL)
			Mix_VolumeChunk(e, vol);
	}
};

