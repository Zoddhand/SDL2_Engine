#include "Player.h"
#include "Collision.h"
#include <iostream>

bool Player::isOnGround;

Player::Player(const char* texturesheet, float x, float y) : GameObject(texturesheet,x,y)
{
	frame.num = 3;
	frame.offset_x = 0;
	frame.offset_y = 8;
	src.h = Engine::tileSize;
	dest.h = Engine::tileSize;
}

void Player::Movement()
{
	if (keys[SDL_SCANCODE_DOWN]) {
		moveDown();
	}
	else if (keys[SDL_SCANCODE_UP]) {
		moveUp();
	}
	if (keys[SDL_SCANCODE_RIGHT]) {
		moveRight();
		frame.flip = SDL_FLIP_NONE;
	}
	else if (keys[SDL_SCANCODE_LEFT]) {
		moveLeft();
		frame.flip = SDL_FLIP_HORIZONTAL;
	}

	if (*getXpos() <= 0)
		setXpos((int)*getXpos());
	else if (*getXpos() >= Engine::mapSizeX - 1)
		setXpos((int)*getXpos());
	if (*getYpos() <= 0)
		setYpos((int)*getYpos());
	else if (*getYpos() >= Engine::mapSizeY - 2)
		setYpos((int)*getYpos());

	PlatformerMove();
}

void Player::update(Map* map)
{
	GameObject::update();
	Collect(map);
}

void Player::PlatformerMove()
{
	if (keys[SDL_SCANCODE_SPACE])
	{
		if (vel.y == 0)
		{
			vel.y = -12.0f;
		}
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
}

void Player::Collect(Map* map)
{
	if (Collision::ItemCollect(map, *getXpos(), *getYpos(), 12, 1))
	{
		// Do stuff if we collect a coin.
	}
}

void Player::moveLeft()
{
	vel.x += (isOnGround ? -20.0f : -15.0f) * Engine::time;
}

void Player::moveRight()
{
	vel.x += (isOnGround ? 25.0f : 15.0f) * Engine::time;
}

void Player::moveUp()
{
	GameObject::moveUp();
}

void Player::moveDown()
{
	GameObject::moveDown();
}