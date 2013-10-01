#pragma once

#include "sprite.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class GamePiece : public The_Sprite
{
private:
	int playercode;
	int rank;
	LPCSTR name;
	bool selection;
	bool isActive;
	bool showRank;

public:
	GamePiece();
	GamePiece(const GamePiece &);
	~GamePiece();
	void init(IDirect3DTexture9*, int);
	GamePiece & operator = (const GamePiece &);

	The_Sprite & getModel();
	void setModel(The_Sprite &);
	IDirect3DTexture9* getTexture();
	void setTexture(IDirect3DTexture9*);
	int getRank();
	void setRank(int);
	LPCSTR getName();
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3);
	bool getActive();
	void setActive(bool);
	bool getShowRank();
	void setShowRank(bool);
	bool checkForCollision(D3DXVECTOR3);
	bool getSelection();
	void setSelection(bool);
	int getPlayerCode();
	void setPlayerCode(int);
};