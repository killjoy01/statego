#pragma once

#include "Player.h"


class GameBoard
{
private:
	Player player[2];
	int Active;

public:
	GameBoard();
	GameBoard(const GameBoard &);
	~GameBoard();
	void init();
	GameBoard & operator = (const GameBoard &);

	Player * getPlayer(int);
	void setPlayer(int, Player *);
	int getActive();
	void setActive(int);
	void displayNewPosition(GamePiece *, D3DXVECTOR3[]);
	bool move(GamePiece * y, D3DXVECTOR3);
	bool checkForCollision(D3DXVECTOR3);
	bool checkForCollision2(D3DXVECTOR3);
	bool makeSelection(D3DXVECTOR3);
};