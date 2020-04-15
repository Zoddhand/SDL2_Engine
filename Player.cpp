#include "Player.h"
#include "Collision.h"
#include <iostream>
#include "Sound.h"

bool Player::isOnGround;
int Player::coins = 0;

Player::Player(const char* texturesheet, float x, float y) : GameObject(texturesheet,x,y)
{
	frame.num = 3;
	frame.offset_x = 0;
	frame.offset_y = 8;
	src.h = Engine::tileSize;
	dest.h = Engine::tileSize;
}

void Player::Movement(int style)
{
	if (style == RPG)
	{
		if (keys[SDL_SCANCODE_DOWN] || Engine::cont.Down) {
			moveDown();
		}
		else if (keys[SDL_SCANCODE_UP] || Engine::cont.Up) {
			moveUp();
		}
		else vel.y = 0; frame.num = 1;
		if (keys[SDL_SCANCODE_RIGHT] || Engine::cont.Right) {
			moveRight(RPG);
		}
		else if (keys[SDL_SCANCODE_LEFT] || Engine::cont.Left) {
			moveLeft(RPG);
		}
		else vel.x = 0; frame.num = 1;

		if (vel.x == 0 && vel.y == 0)
			frame.num = 1;
		else frame.num = 3;
	}
	else if(style == Platformer)
		PlatformerMove();

	if (*getXpos() <= 0)
		setXpos((int)* getXpos());
	else if (*getXpos() >= Engine::mapSizeX - 1)
		setXpos((int)* getXpos());
	if (*getYpos() <= 0)
		setYpos((int)* getYpos());
	else if (*getYpos() >= Engine::mapSizeY - 2)
		setYpos((int)* getYpos());
}

void Player::update(Map* map)
{
	GameObject::update();
	Collect(map);
}

void Player::PlatformerMove()
{
	if (keys[SDL_SCANCODE_RIGHT] || Engine::cont.Right) {
		moveRight(Platformer);
	}
	else if (keys[SDL_SCANCODE_LEFT] || Engine::cont.Left) {
		moveLeft(Platformer);
	}

	if (keys[SDL_SCANCODE_SPACE] || Engine::cont.AButton)
	{
		jump();
	}

	vel.y += 20.0f * Engine::time; // Gravity.

	if (isOnGround) // Slows us to a stop.
	{
		vel.x += -3.0f * vel.x * Engine::time;
		if (fabs(vel.x) < 0.01f)
			vel.x = 0.0f;
	}

	// Clamp velocities
	if (vel.x >  10.0f)
		vel.x =  10.0f;
				 
	if (vel.x <  -10.0f)
		vel.x =  -10.0f;

	if (vel.y> 100.0f)
		vel.y = 100.0f;

	if (vel.y < -100.0f)
		vel.y = -100.0f;

	// Adjust Animations
	if (vel.x == 0)
		frame.num = 1;
	else frame.num = 3;
}

void Player::Collect(Map* map)
{
	if (Collision::ItemCollect(map, *getXpos(), *getYpos(), 12, 0))
	{
		// Do stuff if we collect a coin.
		Sound::playEffect(Engine::effect[0]);
		Player::coins += 1;
	}
}

void Player::moveLeft(int style)
{
	if (style == Platformer)
	{
		vel.x += (isOnGround ? -25.0f : -15.0f) * Engine::time;
	}
	else if (style == RPG)
	{
		vel.x = -15.0f;
	}
	frame.flip = SDL_FLIP_HORIZONTAL;
	frame.offset_y = 8;
}

void Player::moveRight(int style)
{
	if (style == Platformer)
	{
		vel.x += (isOnGround ? 25.0f : 15.0f) * Engine::time;
	}
	else if (style == RPG)
	{
		vel.x = 15.0f;
	}
	frame.flip = SDL_FLIP_NONE;
	frame.offset_y = 8;
}

void Player::moveUp()
{
	vel.y = -15.0f;
	frame.offset_y = 16;
}

void Player::moveDown()
{
	vel.y = 15.0f;
	frame.offset_y = 0;
}

void Player::jump()
{
	if (vel.y == 0 && isOnGround)
	{
		vel.y = -12.0f;
	}
}