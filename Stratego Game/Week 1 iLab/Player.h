#pragma once

#include "GamePiece.h"

class Player
{
private:
	GamePiece piece[40];
	int displayColor;

public:
	Player();
	Player(const Player &);
	~Player();
	void init(int);
	Player & operator = (const Player &);

	GamePiece * getGamePiece(int);
	void setGamePiece(int, GamePiece *);
	int getColor();
	void setColor(int);
};