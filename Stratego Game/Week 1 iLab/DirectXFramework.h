//////////////////////////////////////////////////////////////////////////
// Name:	DirectXFramework.h
// Date:	April 2nd, 2010
// Author:	Kyle Lauing [klauing@devry.edu] or [kylelauing@gmail.com]
// Purpose: This file is used to create a very simple framework for using
//			DirectX 9 for the GSP 381 course for DeVry University.
// Disclaimer:	
//			Copyright © 2010 by DeVry Educational Development Corporation.
//			All rights reserved.  No part of this work may be reproduced 
//			or used in any form or by any means – graphic, electronic, or 
//			mechanical, including photocopying, recording, Web distribution 
//			or information storage and retrieval systems – without the 
//			prior consent of DeVry Educational Development Corporation.
//////////////////////////////////////////////////////////////////////////
#pragma once
#pragma comment(lib, "winmm.lib")
//////////////////////////////////////////////////////////////////////////
// Direct3D 9 headers and libraries required
//////////////////////////////////////////////////////////////////////////
#include "GameBoard.h"
#include "GamePiece.h"
#include "Player.h"
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
#include "fmod.hpp"
#include "dshow.h"
#include <string>
using namespace std;

#pragma comment(lib, "Strmiids.lib")
#pragma comment (lib, "fmodex_vc.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// Macro to release COM objects fast and safely
#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}

typedef enum states
{
	VIDEO,  //legacy, not used
	MENU,	//menu
	INIT,	//init board
	PROGRAM,  //normal game play
	BLANK_BOARD,  //a blank board
	SCOUT,  //scout interface
	CREDITS_SCENE,  //credit scene
	GAME_OVER,  //game over
	QUIT  //quit
};

class CDirectXFramework
{
	//////////////////////////////////////////////////////////////////////////
	// Application Variables
	//////////////////////////////////////////////////////////////////////////
	HWND				m_hWnd;			// Handle to the window
	bool				m_bVsync;		// Boolean for vertical syncing

	//////////////////////////////////////////////////////////////////////////
	// Direct3D Variables
	//////////////////////////////////////////////////////////////////////////
	IDirect3D9*			m_pD3DObject;	// Direct3D 9 Object
	IDirect3DDevice9*	m_pD3DDevice;	// Direct3D 9 Device
	D3DCAPS9			m_D3DCaps;		// Device Capabilities

	//////////////////////////////////////////////////////////////////////////
	// Font Variables
	//////////////////////////////////////////////////////////////////////////
	ID3DXFont*			m_pD3DFont;		// Font ObjecT
	ID3DXFont*			m_pD3DFont2;
	ID3DXFont*			m_classicfont;
	//////////////////////////////////////////////////////////////////////////
	// Sprite Variables
	//////////////////////////////////////////////////////////////////////////
	ID3DXSprite*		m_pD3DSprite;	// Sprite Object
	IDirect3DTexture9*	m_pTexture; 	// Texture Object for a sprite
	IDirect3DTexture9*  w_pTexture[10];
	D3DXIMAGE_INFO		m_imageInfo;	// File details of a texture
	
	IDirectInput8*      m_DInput;
	
	IDirectInputDevice8* m_Keyboard;
	BYTE                 buffer[256];
	bool				 pressed[256];

	IDirectInputDevice8* m_Mouse;
	DIMOUSESTATE2        m_MouseState;
	bool				 mousePressed[8];

	//FMOD
	FMOD::System *system;
	FMOD_RESULT result;
	unsigned int version;
	int numdrivers;
	FMOD_SPEAKERMODE speakermode;
	FMOD_CAPS caps;
	char name[256];

	FMOD::Sound *sound[8];
	FMOD::Channel *channel[3];

	The_Sprite m_sprites[6];
	The_Sprite b_sprites[2];

	The_Sprite menu_sprites[5];
	The_Sprite credits_scene[3];

	states the_state;

	GameBoard gameboard;

	GamePiece g[26];
	D3DXVECTOR3 initPosition;
	int setPiece;
	int pieceType;

	float menuxposition;
	float menuyposition;
	float timer;

	bool gameStart;
	bool levelStart;
	string filename;
	bool scene2;

	D3DXVECTOR3 * movepositions;


public:
	//////////////////////////////////////////////////////////////////////////
	// Init and Shutdown are preferred to constructors and destructor,
	// due to having more control when to explicitly call them when global.
	//////////////////////////////////////////////////////////////////////////
	CDirectXFramework(void);
	~CDirectXFramework(void);

	//////////////////////////////////////////////////////////////////////////
	// Name:		Init
	// Parameters:	HWND hWnd - Handle to the window for the application
	//				HINSTANCE hInst - Handle to the application instance
	//				bool bWindowed - Boolean to control windowed or full-screen
	// Return:		void
	// Description:	Ran once at the start.  Initialize DirectX components and 
	//				variables to control the application.  
	//////////////////////////////////////////////////////////////////////////
	void Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed);

	//////////////////////////////////////////////////////////////////////////
	// Name:		Update
	// Parameters:	float elapsedTime - Time that has elapsed since the last
	//					update call.
	// Return:		void
	// Description: Runs every frame, use dt to limit functionality called to
	//				a certain amount of elapsed time that has passed.  Used 
	//				for updating variables and processing input commands prior
	//				to calling render.
	//////////////////////////////////////////////////////////////////////////
	bool Update(float &);

	//////////////////////////////////////////////////////////////////////////
	// Name:		Render
	// Parameters:	float elapsedTime - Time that has elapsed since the last
	//					render call.
	// Return:		void
	// Description: Runs every frame, use dt to limit functionality called to
	//				a certain amount of elapsed time that has passed.  Render
	//				calls all draw call to render objects to the screen.
	//////////////////////////////////////////////////////////////////////////
	void Render(HWND &, float &);

	//////////////////////////////////////////////////////////////////////////
	// Name:		Shutdown
	// Parameters:	void
	// Return:		void
	// Description:	Runs once at the end of an application.  Destroy COM 
	//				objects and deallocate dynamic memory.
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();

	bool keyDown(BYTE [], float);
	bool keyDown2(BYTE [], GamePiece, int &, D3DXVECTOR3 &, float);
	bool keyDown3(BYTE [], float);
	bool keyDown4(BYTE [], float);
	bool keyDown5(BYTE [], float);

	bool mouseDown();
	bool mouseDown2();
};
