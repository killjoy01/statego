#include "sprite.h"

The_Sprite::The_Sprite()
{
	texture = NULL;
	position = D3DXVECTOR3(0, 0, 0);
	scalex = 0;
	scaley = 0;
	rotation = 0;
	rect.bottom = 0;
	rect.top = 0;
	rect.left = 0;
	rect.right = 0;
}

The_Sprite::The_Sprite(const The_Sprite & s)
{
	texture = s.texture;
	position = s.position;
	scalex = s.scalex;
	scaley = s.scaley;
	rotation = s.rotation;
	rect.bottom = s.rect.bottom;
	rect.top = s.rect.top;
	rect.left = s.rect.left;
	rect.right = s.rect.right;
}

The_Sprite::~The_Sprite()
{
}

void The_Sprite::setTexture(IDirect3DTexture9* t)
{
	texture = t;
}

IDirect3DTexture9* The_Sprite::getTexture()
{
	return texture;
}

void The_Sprite::setPosition(D3DXVECTOR3 p)
{
	position = p;
}

D3DXVECTOR3 The_Sprite::getPosition()
{
	return position;
}

void The_Sprite::setScalex(float s)
{
	scalex = s;
}

float The_Sprite::getScalex()
{
	return scalex;
}

void The_Sprite::setScaley(float s)
{
	scaley = s;
}

float The_Sprite::getScaley()
{
	return scaley;
}

void The_Sprite::setRotation(float r)
{
	rotation = r;
}

float The_Sprite::getRotation()
{
	return rotation;
}

void The_Sprite::setRect(RECT r)
{
	rect = r;
}

RECT The_Sprite::getRect()
{
	return rect;
}
