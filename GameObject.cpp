#include "GameObject.h"
#include "TextureManager.h"
#include "Camera.h"
#include <iostream>

GameObject::GameObject()
{

}

GameObject::GameObject(const char* texturesheet, float x, float y)
{
	tileSize = Engine::tileSize;
	tex = TextureManager::loadTexture(texturesheet);

	pos.x = x / Engine::tileSize;
	pos.y = y / Engine::tileSize;

	src.x = 0;
	src.y = 0;
	src.w = tileSize;
	src.h = tileSize;
	dest.x = pos.x;
	dest.y = pos.y;
	dest.w = tileSize;
	dest.h = tileSize;
}
GameObject::~GameObject()
{
	SDL_DestroyTexture(tex);
	print(tex << " Destroyed.");
}
void GameObject::update()
{
	dest.x = (pos.x - Camera::offX) * tileSize;
	dest.y = (pos.y - Camera::offY) * tileSize;
}
void GameObject::render()
{
	TextureManager::FrameUpdate(&src, frame.num, frame.offset_x, frame.offset_y);
	TextureManager::Draw(tex, src, dest, frame.flip);
	SDL_SetRenderDrawColor(Engine::renderer, 255, 0, 255, 255);
}

void GameObject::moveLeft()
{
	setXvel(-vel.speed * Engine::time);
}
void GameObject::moveRight()
{
	setXvel(vel.speed * Engine::time);
}
void GameObject::moveUp()
{
	setYvel(-vel.speed * Engine::time);
}
void GameObject::moveDown()
{
	setYvel(vel.speed * Engine::time);
}
float* GameObject::getXpos()
{
	return& pos.x;
}
float* GameObject::getYpos()
{
	return& pos.y;
}
void GameObject::setXpos(float x)
{
	pos.x = x;
}
void GameObject::setYpos(float y)
{
	pos.y = y;
}
void GameObject::setXvel(float v)
{
	vel.x = v;
}
void GameObject::setYvel(float v)
{
	vel.y = v;
}
float* GameObject::getXvel()
{
	return& vel.x;
}
float* GameObject::getYvel()
{
	return& vel.y;
}