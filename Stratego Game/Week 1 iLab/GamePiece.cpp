#include "GamePiece.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

GamePiece::GamePiece()
{
	texture = 0;
	rank = 0;
	name = "";
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isActive = false;
	showRank = false;
}

GamePiece::GamePiece(const GamePiece & p)
{
	//model = model;
	texture = p.texture;
	position = p.position;
	scalex = p.scalex;
	scaley = p.scaley;
	rotation = p.rotation;
	texture = p.texture;
	rank = p.rank;
	name = p.name;
	position = p.position;
	isActive = p.isActive;
	showRank = p.showRank;
	rect.bottom = p.rect.bottom;
	rect.top = p.rect.top;
	rect.left = p.rect.left;
	rect.right = p.rect.right;
}

GamePiece::~GamePiece()
{
}

void GamePiece::init(IDirect3DTexture9* t, int r)
{
	//setModel(ModelName);
	setPosition(D3DXVECTOR3(-1.0f, -1.0f, 0.0f));
	setTexture(t);
	setRank(r);
	switch(r)
	{
	case -1:
		name = "FLAG";
		break;
	case 0:
		name = "SPY";
		break;
	case 1:
		name = "SCOUT";
		break;
	case 2:
		name = "MINER";
		break;
	case 3:
		name = "SERGEANT";
		break;
	case 4:
		name = "LIEUTENANT";
		break;
	case 5:
		name = "CAPTAIN";
		break;
	case 6:
		name = "MAJOR";
		break;
	case 7:
		name = "COLONEL";
		break;
	case 8:
		name = "GENERAL";
		break;
	case 9:
		name = "MARSHAL";
		break;
	case 10:
		name = "BOMB";
		break;
	default:
		name = "FLAG";
		break;
	}
	isActive = false;
	showRank = false;
	selection = false;
}

/* Model GamePiece::getModel()
{
	return model;
};

void GamePiece::setModel(Model m)
{
	model = m;
}*/

IDirect3DTexture9* GamePiece::getTexture()
{
	return texture;
}

void GamePiece::setTexture(IDirect3DTexture9* t)
{
	texture = t;
}

int GamePiece::getRank()
{
	return rank;
}

void GamePiece::setRank(int r)
{
	rank = r;
	switch(r)
	{
	case -1:
		name = "FLAG";
		break;
	case 0:
		name = "SPY";
		break;
	case 1:
		name = "SCOUT";
		break;
	case 2:
		name = "MINER";
		break;
	case 3:
		name = "SERGEANT";
		break;
	case 4:
		name = "LIEUTENANT";
		break;
	case 5:
		name = "CAPTAIN";
		break;
	case 6:
		name = "MAJOR";
		break;
	case 7:
		name = "COLONEL";
		break;
	case 8:
		name = "GENERAL";
		break;
	case 9:
		name = "MARSHAL";
		break;
	case 10:
		name = "BOMB";
		break;
	default:
		name = "FLAG";
		break;
	}
}

LPCSTR GamePiece::getName()
{
	return name;
}

D3DXVECTOR3 GamePiece::getPosition()
{
	return position;
}

void GamePiece::setPosition(D3DXVECTOR3 p)
{
	position = p;
}

bool GamePiece::getActive()
{
	return isActive;
}

void GamePiece::setActive(bool a)
{
	isActive = a;
}

bool GamePiece::getShowRank()
{
	return showRank;
}

void GamePiece::setShowRank(bool s)
{
	showRank = s;
}

bool GamePiece::checkForCollision(D3DXVECTOR3 p)
{
	if (position == p)
	{
		if (isActive)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

GamePiece & GamePiece::operator = (const GamePiece & p)
{
	texture = p.texture;
	position = p.position;
	scalex = p.scalex;
	scaley = p.scaley;
	rotation = p.rotation;
	rank = p.rank;
	name = p.name;
	isActive = p.isActive;
	showRank = p.showRank;
	rect.bottom = p.rect.bottom;
	rect.top = p.rect.top;
	rect.left = p.rect.left;
	rect.right = p.rect.right;
	return *this;
}

bool GamePiece::getSelection()
{
	return selection;
}

void GamePiece::setSelection(bool s)
{
	selection = s;
}

int GamePiece::getPlayerCode()
{
	return playercode;
}

void GamePiece::setPlayerCode(int p)
{
	playercode = p;
}



