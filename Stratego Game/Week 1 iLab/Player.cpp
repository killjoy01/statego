#include "Player.h"
#include "GamePiece.h"

Player::Player()
{
	for (int i = 0; i < 40; i++)
	{
		piece[i].init(0, -1);
		displayColor = 0;
	}
}

Player::Player(const Player & p)
{
	for (int i = 0; i < 40; i++)
	{
		piece[i] = p.piece[i];
	}
	displayColor = p.displayColor;
}

Player::~Player()
{
}

void Player::init(int c)
{
	if (c == 1)
	{
		displayColor = 0;
	}
	else if (c == 2)
	{
		displayColor = 1;
	}
}

Player & Player::operator = (const Player & p)
{
	for (int i = 0; i < 40; i++)
	{
		piece[i] = p.piece[i];
	}
	displayColor = p.displayColor;
	return *this;
}

GamePiece * Player::getGamePiece(int i)
{
	return &piece[i];
}

void Player::setGamePiece(int i, GamePiece * g)
{
	piece[i] = *g;
}

int Player::getColor()
{
	return displayColor;
}

void Player::setColor(int c)
{
	if (c == 1)
	{
		displayColor = 0;
	}
	else
	{
		displayColor = 1;
	}
}
