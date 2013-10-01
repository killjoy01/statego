#include "GameBoard.h"
#include "Player.h"
#include <vector>
using namespace std;

GameBoard::GameBoard()
{
	player[0].init(1);
	player[1].init(2);
	Active = false;
}

GameBoard::GameBoard(const GameBoard & g)
{
	player[0] = g.player[0];
	player[1] = g.player[1];
	Active = g.Active;
}

GameBoard::~GameBoard()
{
}

void GameBoard::init()
{
}

GameBoard & GameBoard::operator = (const GameBoard & g)
{
	player[0] = g.player[0];
	player[1] = g.player[1];
	Active = g.Active;
	return *this;
}

Player * GameBoard::getPlayer(int i)
{
	return &player[i];
}

void GameBoard::setPlayer(int i, Player * p)
{
	player[i] = *p;
}
int GameBoard::getActive()
{
	return Active;
}

void GameBoard::setActive(int a)
{
	Active = a;
}

void GameBoard::displayNewPosition(GamePiece * p, D3DXVECTOR3 spacesfound[])
{
	for (int j = 0; j < 20; j++)
	{
		spacesfound[j] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	}
	int i = 0;
	float left = p->getPosition().x - 1.0f, right = p->getPosition().x + 1.0f, up = p->getPosition().y - 1.0f, down = p->getPosition().y + 1.0f;
	bool flagleft = true, flagright = true, flagup = true, flagdown = true;
	while (flagleft)
	{
		if (checkForCollision2(D3DXVECTOR3(left, p->getPosition().y, 0.0f)))
		{
			flagleft = false;
		}
		else if (checkForCollision(D3DXVECTOR3(left, p->getPosition().y, 0.0f)))
		{
			spacesfound[i] = D3DXVECTOR3(left, p->getPosition().y, 0.0f);
			i++;
			flagleft = false;
		}
		else if (left == -1.0f)
		{
			flagleft = false;
		}
		else
		{
			spacesfound[i] = D3DXVECTOR3(left, p->getPosition().y, 0.0f);
			i++;
			left = left - 1.0f;
		}
	}
	while (flagright)
	{
		if (checkForCollision2(D3DXVECTOR3(right, p->getPosition().y, 0.0f)))
		{
			flagright = false;
		}
		else if (checkForCollision(D3DXVECTOR3(right, p->getPosition().y, 0.0f)))
		{
			spacesfound[i] = D3DXVECTOR3(right, p->getPosition().y, 0.0f);
			i++;
			flagright = false;
		}
		else if (right > 9.0f)
		{
			flagright = false;
		}
		else
		{
			spacesfound[i] = D3DXVECTOR3(right, p->getPosition().y, 0.0f);
			i++;
			right = right + 1.0f;
		}
	}
	while (flagup)
	{
		if (checkForCollision2(D3DXVECTOR3(p->getPosition().x, up, 0.0f)))
		{
			flagup = false;
		}
		else if (checkForCollision(D3DXVECTOR3(p->getPosition().x, up, 0.0f)))
		{
			spacesfound[i] = D3DXVECTOR3(p->getPosition().x, up, 0.0f);
			i++;
			flagup = false;
		}
		else if (up < 0.0f)
		{
			flagup = false;
		}
		else
		{
			spacesfound[i] = D3DXVECTOR3(p->getPosition().x, up, 0.0f);
			i++;
			up = up - 1.0f;
		}
	}
	while (flagdown)
	{
		if (checkForCollision2(D3DXVECTOR3(p->getPosition().x, down, 0.0f)))
		{
			flagdown = false;
		}
		else if (checkForCollision(D3DXVECTOR3(p->getPosition().x, down, 0.0f)))
		{
			spacesfound[i] = D3DXVECTOR3(p->getPosition().x, down, 0.0f);
			i++;
			flagdown = false;
		}
		else if (down > 9.0f)
		{
			flagdown = false;
		}
		else
		{
			spacesfound[i] = D3DXVECTOR3(p->getPosition().x, down, 0.0f);
			i++;
			down = down + 1.0f;
		}
	}
}

bool GameBoard::move(GamePiece * y, D3DXVECTOR3 p)
{
	//moves one position
	if (Active == 0)
	{
		if (checkForCollision(p))
		{
			GamePiece * g;
			for (int i = 0; i < 40; i++)
			{
				if ((player[1].getGamePiece(i)->getPosition() == p) && (player[1].getGamePiece(i)->getActive()))
				{
					g = player[1].getGamePiece(i);
				}
			}
			if ((y->getRank() == 0) && (g->getRank() == 9))  //spy removing the marshal
			{
				g->setActive(false);
				y->setPosition(p);
				y->setShowRank(true);
				return true;
			}
			else if ((y->getRank() == 2) && (g->getRank() == 10)) //miner removing the bomb
			{
				g->setActive(false);
				y->setPosition(p);
				y->setShowRank(true);
				return true;
			}
			else if (y->getRank() == g->getRank())  //if the ranks are a tie
			{
				g->setActive(false);
				y->setActive(false);
				return true;
			}
			else if (y->getRank() > g->getRank())  // your rank is greater than their rank
			{
				g->setActive(false);
				y->setPosition(p);
				y->setShowRank(true);
				return true;
			}
			else //you are lower rank than the opponent
			{
				y->setActive(false);
				g->setShowRank(true);
				return true;
			}
		}
		else //move to that position
		{
			if ((p.x < 0.0f) || (p.x > 9.0f) || (p.y < 0.0f) || (p.y > 9.0f))
			{
				return false;
			}
			else
			{
				for (int i = 0; i < 40; i++)
				{
					if ((p == player[0].getGamePiece(i)->getPosition()) && (player[0].getGamePiece(i)->getActive()))
					{
						return false;
					}
				}
				y->setPosition(p);
				return true;
			}
		}
	}
	else if (Active == 1)
	{
		if (checkForCollision(p))
		{
			GamePiece * g;
			for (int i = 0; i < 40; i++)
			{
				if ((player[0].getGamePiece(i)->getPosition() == p) && (player[0].getGamePiece(i)->getActive()))
				{
					g = player[0].getGamePiece(i);
				}
			}
			if ((y->getRank() == 0) && (g->getRank() == 9))
			{
				g->setActive(false);
				y->setPosition(p);
				y->setShowRank(true);
			}
			else if ((y->getRank() == 2) && (g->getRank() == 10))
			{
				g->setActive(false);
				y->setPosition(p);
				y->setShowRank(true);
			}
			else if (y->getRank() == g->getRank())
			{
				g->setActive(false);
				y->setActive(false);
				return true;
			}
			else if (y->getRank() > g->getRank())
			{
				g->setActive(false);
				y->setPosition(p);
				y->setShowRank(true);
			}
			else
			{
				y->setActive(false);
				g->setShowRank(true);
			}
		}
		else
		{
			if ((p.x < 0.0f) || (p.x > 9.0f) || (p.y < 0.0f) || (p.y > 9.0f))
			{
				return false;
			}
			else
			{
				for (int i = 0; i < 40; i++)
				{
					if ((p == player[1].getGamePiece(i)->getPosition()) && (player[1].getGamePiece(i)->getActive()))
					{
						return false;
					}
				}
				y->setPosition(p);
				return true;
			}
		}
	}
	return true;
}

bool GameBoard::checkForCollision(D3DXVECTOR3 p)
{
	for (int i = 0; i < 40; i++)
	{
		if (Active == 0)
		{
			if (player[1].getGamePiece(i)->checkForCollision(p))
			{
				return true;
			}
		}
		else if (Active == 1)
		{
			if (player[0].getGamePiece(i)->checkForCollision(p))
			{
				return true;
			}
		}
	}
	return false;
}

bool GameBoard::checkForCollision2(D3DXVECTOR3 p)
{
	for (int i = 0; i < 40; i++)
	{
		if (player[Active].getGamePiece(i)->checkForCollision(p))
		{
			return true;
		}
	}
	return false;
}

bool GameBoard::makeSelection(D3DXVECTOR3 p)
{
	for (int i = 0; i < 40; i++)
	{
		player[0].getGamePiece(i)->setSelection(false);
		player[1].getGamePiece(i)->setSelection(false);
	}
	if (Active == 0)
	{
		GamePiece *g = NULL;
		for (int i = 0; i < 40; i++)
		{
			if ((player[0].getGamePiece(i)->getPosition() == p) && (player[0].getGamePiece(i)->getActive()))
			{
				g = player[0].getGamePiece(i);
			}
		}
		if (g == NULL)
		{
			return false;
		}
		if ((g->getRank() == 10) || (g->getRank() == -1))
		{
			return false;
		}
		else
		{
			g->setSelection(true);
			return true;
		}
	}
	else if (Active == 1)
	{
		GamePiece *g = NULL;
		for (int i = 0; i < 40; i++)
		{
			if ((player[1].getGamePiece(i)->getPosition() == p) && (player[0].getGamePiece(i)->getActive()))
			{
				g = player[1].getGamePiece(i);
			}
		}
		if (g == NULL)
		{
			return false;
		}
		if ((g->getRank() == 10) || (g->getRank() == -1))
		{
			return false;
		}
		else
		{
			g->setSelection(true);
			return true;
		}
		return false;
	}
}

