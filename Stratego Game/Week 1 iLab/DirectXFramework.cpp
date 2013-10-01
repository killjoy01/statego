//////////////////////////////////////////////////////////////////////////
// Name:	DirectXFramework.cpp
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
#include "DirectXFramework.h"
#include "sprite.h"
#include "GameBoard.h"
#include "GamePiece.h"
#include "Player.h"
#include "fmod.hpp"
#include "dshow.h"
#include <string>
#include <Windows.h>
using namespace std;

#define DIRECTINPUT_VERSION 0x0800

D3DXMATRIX & calculateMatrix(int, int, float, float, float);
bool keyDown(BYTE [], The_Sprite &, float);
bool mouseDown(DIMOUSESTATE2, The_Sprite &, int &);


CDirectXFramework::CDirectXFramework(void)
{
	// Init or NULL objects before use to avoid any undefined behavior
	m_bVsync		= false;
	m_pD3DObject	= 0;
	m_pD3DDevice	= 0;
	
}

CDirectXFramework::~CDirectXFramework(void)
{
	// If Shutdown is not explicitly called correctly, call it when 
	// this class is destroyed or falls out of scope as an error check.
	Shutdown();
}

void CDirectXFramework::Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed)
{
	CoInitialize(NULL);

	m_hWnd = hWnd;

	//////////////////////////////////////////////////////////////////////////
	// Direct3D Foundations - D3D Object, Present Parameters, and D3D Device
	//////////////////////////////////////////////////////////////////////////

	// Create the D3D Object
	m_pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);

	// Find the width and height of window using hWnd and GetWindowRect()
	RECT rect;
	GetWindowRect(hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// Set D3D Device presentation parameters before creating the device
	D3DPRESENT_PARAMETERS D3Dpp;
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));  // NULL the structure's memory

	D3Dpp.hDeviceWindow					= hWnd;										// Handle to the focus window
	D3Dpp.Windowed						= bWindowed;								// Windowed or Full-screen boolean
	D3Dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;								// Format of depth/stencil buffer, 24 bit depth, 8 bit stencil
	D3Dpp.EnableAutoDepthStencil		= TRUE;										// Enables Z-Buffer (Depth Buffer)
	D3Dpp.BackBufferCount				= 1;										// Change if need of > 1 is required at a later date
	D3Dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;							// Back-buffer format, 8 bits for each pixel
	D3Dpp.BackBufferHeight				= height;									// Make sure resolution is supported, use adapter modes
	D3Dpp.BackBufferWidth				= width;									// (Same as above)
	D3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;					// Discard back-buffer, must stay discard to support multi-sample
	D3Dpp.PresentationInterval			= m_bVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE; // Present back-buffer immediately, unless V-Sync is on								
	D3Dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// This flag should improve performance, if not set to NULL.
	D3Dpp.FullScreen_RefreshRateInHz	= bWindowed ? 0 : D3DPRESENT_RATE_DEFAULT;	// Full-screen refresh rate, use adapter modes or default
	D3Dpp.MultiSampleQuality			= 0;										// MSAA currently off, check documentation for support.
	D3Dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;						// MSAA currently off, check documentation for support.

	// Check device capabilities
	DWORD deviceBehaviorFlags = 0;
	m_pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	// Determine vertex processing mode
	if(m_D3DCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		// Hardware vertex processing supported? (Video Card)
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	}
	else
	{
		// If not, use software (CPU)
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	}
	
	// If hardware vertex processing is on, check pure device support
	if(m_D3DCaps.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;	
	}
	
	// Create the D3D Device with the present parameters and device flags above
	m_pD3DObject->CreateDevice(
		D3DADAPTER_DEFAULT,		// which adapter to use, set to primary
		D3DDEVTYPE_HAL,			// device type to use, set to hardware rasterization
		hWnd,					// handle to the focus window
		deviceBehaviorFlags,	// behavior flags
		&D3Dpp,					// presentation parameters
		&m_pD3DDevice);			// returned device pointer

	//*************************************************************************

	//////////////////////////////////////////////////////////////////////////
	// Create a Font Object
	//////////////////////////////////////////////////////////////////////////
	
	// Load a font for private use for this process


	// Load D3DXFont, each font style you want to support will need an ID3DXFont



	//////////////////////////////////////////////////////////////////////////
	// Create Sprite Object and Textures
	//////////////////////////////////////////////////////////////////////////

	// Create a sprite object, note you will only need one for all 2D sprites


	// Create a texture, each different 2D sprite to display to the screen
	// will need a new texture object.  If drawing the same sprite texture
	// multiple times, just call that sprite's Draw() with different 
	// transformation values.


	//*************************************************************************
	AddFontResourceEx(L"Delicious-Roman.otf", NULL, 0);
	D3DXCreateFont(m_pD3DDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                         L"Delicious-Roman.otf", &m_pD3DFont);
	AddFontResourceEx(L"Delicious-Roman.otf", NULL, 0);
	D3DXCreateFont(m_pD3DDevice, 64, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                         L"Delicious-Roman.otf", &m_pD3DFont2);
	AddFontResourceEx(L"C:\Windows\Fonts\Alibi___.ttf", NULL, 0);
	D3DXCreateFont(m_pD3DDevice, 24, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                         L"C:\Windows\Fonts\Alibi___.ttf", &m_classicfont);
	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);
	
	

	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_DInput, 0);

	m_DInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard, 0);
	m_DInput->CreateDevice(GUID_SysMouse, &m_Mouse, 0);
	m_Keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	m_Mouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	m_Mouse->SetDataFormat(&c_dfDIMouse2);

	//FMOD input

	result = FMOD::System_Create(&system);
	//ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
	}
	result = system->getNumDrivers(&numdrivers);
	//ERRCHECK(result);

	if (numdrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		//ERRCHECK(result);
	}
	else
	{
		result = system->getDriverCaps(0, &caps, 0, &speakermode);
		//ERRCHECK(result);
	}

	result = system->setSpeakerMode(speakermode);
	//ERRCHECK(result);

	if (caps & FMOD_CAPS_HARDWARE_EMULATED)
	{
		result = system->setDSPBufferSize(1024, 10);
		//ERRCHECK(result);
	}

	result = system->getDriverInfo(0, name, 256, 0);
	//ERRCHECK(result);

	if (strstr(name, "SigmaTel"))
	{
		result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
		//ERRCHECK(result);
	}

	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		//ERRCHECK(result);

		result = system->init(100, FMOD_INIT_NORMAL, 0);
	}
	
	//grass sprite
	m_sprites[0].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_sprites[0].setRotation(0.0f);
	m_sprites[0].setScalex(1.0f);
	m_sprites[0].setScaley(1.0f);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"test3.tga", &m_pTexture);
	m_sprites[0].setTexture(m_pTexture);

	m_sprites[1].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_sprites[1].setRotation(0.0f);
	m_sprites[1].setScalex(1.0f);
	m_sprites[1].setScaley(1.0f);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"promptbox.jpg", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0, 0), NULL, NULL, &m_pTexture);
	m_sprites[1].setTexture(m_pTexture);
	//selector sprite
	
	m_sprites[2].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_sprites[2].setRotation(0.0f);
	m_sprites[2].setScalex(1.0f);
	m_sprites[2].setScaley(1.0f);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"selector.tga", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0, 0), NULL, NULL, &m_pTexture);
	m_sprites[2].setTexture(m_pTexture);

	//menu sprites

	m_sprites[3].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_sprites[3].setRotation(0.0f);
	m_sprites[3].setScalex(1.0f);
	m_sprites[3].setScaley(1.0f);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"strategopiece.tga", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0, 0), NULL, NULL, &m_pTexture);
	m_sprites[3].setTexture(m_pTexture);

	m_sprites[4].setPosition(D3DXVECTOR3(272.0f, 93.0f, 0.0f));
	m_sprites[4].setRotation(0.0f);
	m_sprites[4].setScalex(1.0f);
	m_sprites[4].setScaley(1.0f);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"strategotitle.jpg", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0, 0), NULL, NULL, &m_pTexture);
	m_sprites[4].setTexture(m_pTexture);

	//selection sprite for scouts
	
	m_sprites[5].setPosition(D3DXVECTOR3(272.0f, 93.0f, 0.0f));
	m_sprites[5].setRotation(0.0f);
	m_sprites[5].setScalex(1.0f);
	m_sprites[5].setScaley(1.0f);
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"selectspace.jpg", D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, D3DUSAGE_DYNAMIC,
		D3DFMT_FROM_FILE, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0, 0), NULL, NULL, &m_pTexture);
	m_sprites[5].setTexture(m_pTexture);

	//sprite pieces
	
	gameboard.init();
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redmarshal.jpg", &m_pTexture);
	g[0].setTexture(m_pTexture);
	initPosition = D3DXVECTOR3(0.0f, 9.0f, 0.0f);
	g[0].setRotation(0.0f);
	g[0].setScalex(1.0f);
	g[0].setScaley(1.0f);
	g[0].setRank(9);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redgeneral.jpg", &m_pTexture);
	g[1].setTexture(m_pTexture);
	g[1].setRotation(0.0f);
	g[1].setScalex(1.0f);
	g[1].setScaley(1.0f);
	g[1].setRank(8);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redcolonel.jpg", &m_pTexture);
	g[2].setTexture(m_pTexture);
	g[2].setRotation(0.0f);
	g[2].setScalex(1.0f);
	g[2].setScaley(1.0f);
	g[2].setRank(7);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redmajor.jpg", &m_pTexture);
	g[3].setTexture(m_pTexture);
	g[3].setRotation(0.0f);
	g[3].setScalex(1.0f);
	g[3].setScaley(1.0f);
	g[3].setRank(6);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redcaptain.jpg", &m_pTexture);
	g[4].setTexture(m_pTexture);
	g[4].setRotation(0.0f);
	g[4].setScalex(1.0f);
	g[4].setScaley(1.0f);
	g[4].setRank(5);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redlieutenant.jpg", &m_pTexture);
	g[5].setTexture(m_pTexture);
	g[5].setRotation(0.0f);
	g[5].setScalex(1.0f);
	g[5].setScaley(1.0f);
	g[5].setRank(4);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redsergeant.jpg", &m_pTexture);
	g[6].setTexture(m_pTexture);
	g[6].setRotation(0.0f);
	g[6].setScalex(1.0f);
	g[6].setScaley(1.0f);
	g[6].setRank(3);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redminer.jpg", &m_pTexture);
	g[7].setTexture(m_pTexture);
	g[7].setRotation(0.0f);
	g[7].setScalex(1.0f);
	g[7].setScaley(1.0f);
	g[7].setRank(2);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redscout.jpg", &m_pTexture);
	g[8].setTexture(m_pTexture);
	g[8].setRotation(0.0f);
	g[8].setScalex(1.0f);
	g[8].setScaley(1.0f);
	g[8].setRank(1);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redspy.jpg", &m_pTexture);
	g[9].setTexture(m_pTexture);
	g[9].setRotation(0.0f);
	g[9].setScalex(1.0f);
	g[9].setScaley(1.0f);
	g[9].setRank(0);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redbomb.jpg", &m_pTexture);
	g[10].setTexture(m_pTexture);
	g[10].setRotation(0.0f);
	g[10].setScalex(1.0f);
	g[10].setScaley(1.0f);
	g[10].setRank(10);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"redflag.jpg", &m_pTexture);
	g[11].setTexture(m_pTexture);
	g[11].setRotation(0.0f);
	g[11].setScalex(1.0f);
	g[11].setScaley(1.0f);
	g[11].setRank(-1);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluemarshal.jpg", &m_pTexture);
	g[12].setTexture(m_pTexture);
	g[12].setRotation(0.0f);
	g[12].setScalex(1.0f);
	g[12].setScaley(1.0f);
	g[12].setRank(9);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluegeneral.jpg", &m_pTexture);
	g[13].setTexture(m_pTexture);
	g[13].setRotation(0.0f);
	g[13].setScalex(1.0f);
	g[13].setScaley(1.0f);
	g[13].setRank(8);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluecolonel.jpg", &m_pTexture);
	g[14].setTexture(m_pTexture);
	g[14].setRotation(0.0f);
	g[14].setScalex(1.0f);
	g[14].setScaley(1.0f);
	g[14].setRank(7);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluemajor.jpg", &m_pTexture);
	g[15].setTexture(m_pTexture);
	g[15].setRotation(0.0f);
	g[15].setScalex(1.0f);
	g[15].setScaley(1.0f);
	g[15].setRank(6);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluecaptain.jpg", &m_pTexture);
	g[16].setTexture(m_pTexture);
	g[16].setRotation(0.0f);
	g[16].setScalex(1.0f);
	g[16].setScaley(1.0f);
	g[16].setRank(5);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluelieutenant.jpg", &m_pTexture);
	g[17].setTexture(m_pTexture);
	g[17].setRotation(0.0f);
	g[17].setScalex(1.0f);
	g[17].setScaley(1.0f);
	g[17].setRank(4);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluesergeant.jpg", &m_pTexture);
	g[18].setTexture(m_pTexture);
	g[18].setRotation(0.0f);
	g[18].setScalex(1.0f);
	g[18].setScaley(1.0f);
	g[18].setRank(3);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"blueminer.jpg", &m_pTexture);
	g[19].setTexture(m_pTexture);
	g[19].setRotation(0.0f);
	g[19].setScalex(1.0f);
	g[19].setScaley(1.0f);
	g[19].setRank(2);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluescout.jpg", &m_pTexture);
	g[20].setTexture(m_pTexture);
	g[20].setRotation(0.0f);
	g[20].setScalex(1.0f);
	g[20].setScaley(1.0f);
	g[20].setRank(1);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluespy.jpg", &m_pTexture);
	g[21].setTexture(m_pTexture);
	g[21].setRotation(0.0f);
	g[21].setScalex(1.0f);
	g[21].setScaley(1.0f);
	g[21].setRank(0);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"bluebomb.jpg", &m_pTexture);
	g[22].setTexture(m_pTexture);
	g[22].setRotation(0.0f);
	g[22].setScalex(1.0f);
	g[22].setScaley(1.0f);
	g[22].setRank(10);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"blueflag.jpg", &m_pTexture);
	g[23].setTexture(m_pTexture);
	g[23].setRotation(0.0f);
	g[23].setScalex(1.0f);
	g[23].setScaley(1.0f);
	g[23].setRank(-1);
	
	setPiece = 0;
	pieceType = 0;

	//blank sprites

	D3DXCreateTextureFromFile(m_pD3DDevice, L"redblank.jpg", &m_pTexture);
	b_sprites[0].setTexture(m_pTexture);
	b_sprites[0].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	b_sprites[0].setRotation(0.0f);
	b_sprites[0].setScalex(1.0f);
	b_sprites[0].setScaley(1.0f);
	D3DXCreateTextureFromFile(m_pD3DDevice, L"blueblank.jpg", &m_pTexture);
	b_sprites[1].setTexture(m_pTexture);
	b_sprites[1].setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	b_sprites[1].setRotation(0.0f);
	b_sprites[1].setScalex(1.0f);
	b_sprites[1].setScaley(1.0f);
	
	for (int i = 0; i < 256; i++)
	{
		pressed[i] = false;
	}

	for (int i = 0; i < 8; i++)
	{
		mousePressed[i] = false;
	}

	gameboard.setActive(0);
	timer = 0.0f;

	the_state = MENU;

	gameStart = true;
	scene2 = false;

	menuyposition = 250;

	movepositions = new D3DXVECTOR3[20];
}

bool CDirectXFramework::Update(float & dt)
{
	GamePiece * p = NULL;
	bool playingmusic = false;
	long evCode;
    LONG_PTR eventParam1, eventParam2;
	m_Keyboard->Acquire();
	m_Mouse->Acquire();
	m_Keyboard->GetDeviceState(sizeof(buffer), (void **)&buffer);
	m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void **)&m_MouseState);
	switch(the_state)
	{
	case MENU:
		//playingmusic = false;
		//channel[1]->isPlaying(&playingmusic);
		//if (!playingmusic)
		//{
		//	result = system->playSound(FMOD_CHANNEL_FREE, sound[6], false, &channel[1]);
		//}
		keyDown4(buffer, dt);
		break;
	case INIT:
		if (gameboard.getActive() == 0)
		{
			if (setPiece == 0)
			{
				pieceType = 0;
			}
			else if (setPiece == 1)
			{
				pieceType = 1;
			}
			else if ((setPiece >= 2) && (setPiece <= 3))
			{
				pieceType = 2;
			}
			else if ((setPiece >= 4) && (setPiece <= 6))
			{
				pieceType = 3;
			}
			else if ((setPiece >= 7) && (setPiece <= 10))
			{
				pieceType = 4;
			}
			else if ((setPiece >= 11) && (setPiece <= 14))
			{
				pieceType = 5;
			}
			else if ((setPiece >= 15) && (setPiece <= 18))
			{
				pieceType = 6;
			}
			else if ((setPiece >= 19) && (setPiece <= 23))
			{
				pieceType = 7;
			}
			else if ((setPiece >= 24) && (setPiece <= 31))
			{
				pieceType = 8;
			}
			else if (setPiece == 32)
			{
				pieceType = 9;
			}
			else if ((setPiece >= 23) && (setPiece <= 38))
			{
				pieceType = 10;
			}
			else if (setPiece == 39)
			{
				pieceType = 11;
			}
			else if (setPiece == 40)
			{
				gameboard.setActive(1);
				setPiece = 0;
				pieceType = 12;
				initPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				the_state = BLANK_BOARD;
				return false;
			}
			else
			{
				return false;
			}
		}
		else if (gameboard.getActive() == 1)
		{
			if (setPiece == 0)
			{
				pieceType = 12;
			}
			else if (setPiece == 1)
			{
				pieceType = 13;
			}
			else if ((setPiece >= 2) && (setPiece <= 3))
			{
				pieceType = 14;
			}
			else if ((setPiece >= 4) && (setPiece <= 6))
			{
				pieceType = 15;
			}
			else if ((setPiece >= 7) && (setPiece <= 10))
			{
				pieceType = 16;
			}
			else if ((setPiece >= 11) && (setPiece <= 14))
			{
				pieceType = 17;
			}
			else if ((setPiece >= 15) && (setPiece <= 18))
			{
				pieceType = 18;
			}
			else if ((setPiece >= 19) && (setPiece <= 23))
			{
				pieceType = 19;
			}
			else if ((setPiece >= 24) && (setPiece <= 31))
			{
				pieceType = 20;
			}
			else if (setPiece == 32)
			{
				pieceType = 21;
			}
			else if ((setPiece >= 23) && (setPiece <= 38))
			{
				pieceType = 22;
			}
			else if (setPiece == 39)
			{
				pieceType = 23;
			}
			else if (setPiece == 40)
			{
				gameboard.setActive(0);
				the_state = BLANK_BOARD;
				return false;
			}
			else
			{
				return false;
			}
		}
		keyDown2(buffer, g[pieceType], setPiece, initPosition, dt);
		break;
	case PROGRAM:
		mouseDown();
		for (int i = 0; i < 40; i++)
		{
			if ((gameboard.getPlayer(gameboard.getActive())->getGamePiece(i)->getSelection()) && 
				(gameboard.getPlayer(gameboard.getActive())->getGamePiece(i)->getActive()))
			{
				 p = gameboard.getPlayer(gameboard.getActive())->getGamePiece(i);
			}
		}
		if (p != NULL) 
		{
			if (p->getRank() == 1)
			{
				the_state = SCOUT;
				return false;
			}
		}
		keyDown(buffer, dt);
		if ((gameboard.getPlayer(0)->getGamePiece(39)->getActive() == false) || (gameboard.getPlayer(1)->getGamePiece(39)->getActive() == false))
		{
			MessageBox(NULL, L"You Win!", L"", MB_OK);
			gameboard = GameBoard();
			the_state = MENU;
			gameboard.setActive(0);
			pieceType = 0;
			setPiece = 0;
			initPosition = D3DXVECTOR3(0.0f, 9.0f, 0.0f);
		}
		break;
	case BLANK_BOARD:
		MessageBox(NULL, L"Press OK To Continue", L"", MB_OK);
		if (gameboard.getActive() == 1)
		{
			the_state = INIT;
		}
		else if (gameboard.getActive() == 0)
		{
			the_state = PROGRAM;
		}
		//keyDown3(buffer, dt);
		break;
	case SCOUT:
		for (int i = 0; i < 40; i++)
		{
			if ((gameboard.getPlayer(gameboard.getActive())->getGamePiece(i)->getSelection()) 
				&& (gameboard.getPlayer(gameboard.getActive())->getGamePiece(i)->getActive()))
			{
				p = gameboard.getPlayer(gameboard.getActive())->getGamePiece(i);
				i = 40;
			}
		}
		gameboard.displayNewPosition(p, movepositions);
		mouseDown2();
	case CREDITS_SCENE:
		keyDown5(buffer, dt);
		break;
	case GAME_OVER:
		break;
	case QUIT:
		return true;
		break;
	}
	return false;
	
}


void CDirectXFramework::Render(HWND & hWnd, float & dt)
{
	if (the_state == MENU)
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		rect.right = rect.right - rect.left;
		rect.bottom = rect.bottom - rect.top;
		rect.left = 0;
		rect.top = 0;

		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
			
		world = calculateMatrix(200, (menuyposition - 32.0f),
								m_sprites[3].getScalex(),
								m_sprites[3].getScaley(),									
								m_sprites[3].getRotation());
		m_pD3DSprite->SetTransform(&world);
		m_pD3DSprite->Draw(m_sprites[3].getTexture(), NULL, 
						   &D3DXVECTOR3((float)(32 + 200), 
						   (float)(menuyposition), 0),
						   &D3DXVECTOR3((float)(200 + 32), 
						   (float)(menuyposition + 32), 0), 
							D3DCOLOR_ARGB(255, 255, 255, 255));

		world = calculateMatrix(m_sprites[4].getPosition().x, (m_sprites[4].getPosition().y),
								m_sprites[4].getScalex(),
								m_sprites[4].getScaley(),									
								m_sprites[4].getRotation());
		m_pD3DSprite->SetTransform(&world);
		m_pD3DSprite->Draw(m_sprites[4].getTexture(), NULL, 
						   &D3DXVECTOR3((float)(128 + m_sprites[4].getPosition().x), 
						   (float)(m_sprites[4].getPosition().y), 0),
						   &D3DXVECTOR3((float)(m_sprites[4].getPosition().x + 128), 
						   (float)(m_sprites[4].getPosition().y + 32), 0), 
							D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pD3DSprite->End();

		m_pD3DDevice->EndScene();
		
		m_pD3DDevice->BeginScene();

		m_pD3DSprite->Begin(NULL);

		RECT displayclip;
		displayclip.top = 250;
		displayclip.left = 300;
		displayclip.bottom = 640;
		displayclip.right = 800;

		wchar_t buffer[64];
		
		swprintf_s(buffer, 64, L"lY: %f", m_MouseState.lY);

		m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		wchar_t buffer2[64];
		
		swprintf_s(buffer, 64, L"%s", L"PLAY");

		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		displayclip.top = 325;

		swprintf_s(buffer, 64, L"%s", L"CREDITS SCENE");

		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		displayclip.top = 400;

		swprintf_s(buffer, 64, L"%s", L"QUIT");

		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
		
		m_pD3DSprite->End();

		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	}
	if (the_state == INIT)
	{
		float numFrames = 0.0f;
		float timeElapsed = 0.0f;
		float mFPS = 0.0f;

		RECT rect;
		GetWindowRect(hWnd, &rect);
		rect.right = rect.right - rect.left;
		rect.bottom = rect.bottom - rect.top;
		rect.left = 0;
		rect.top = 0;

		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				world = calculateMatrix(i * 64, j * 64, m_sprites[0].getScalex(), 
					                    m_sprites[0].getScaley(), m_sprites[0].getRotation());
				m_pD3DSprite->SetTransform(&world);
				m_pD3DSprite->Draw(m_sprites[0].getTexture(), NULL, &D3DXVECTOR3((float)(32 + (i * 64)), (float)(32 + (j * 64)), 0),
								   &D3DXVECTOR3((float)((i * 64) + 32), (float)((j * 64) + 32), 0), 
							       D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 0)
			{
				if (gameboard.getPlayer(0)->getGamePiece(i)->getActive())
				{
					world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
											(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
											gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
											gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
											gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
					m_pD3DSprite->SetTransform(&world);
					m_pD3DSprite->Draw(gameboard.getPlayer(0)->getGamePiece(i)->getTexture(), NULL, 
									   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
									   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
									   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
									   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}
			else if (gameboard.getActive() == 1)
			{
				if (gameboard.getPlayer(0)->getGamePiece(i)->getActive())
				{
					world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
											(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
											gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
											gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
											gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
					m_pD3DSprite->SetTransform(&world);
					m_pD3DSprite->Draw(b_sprites[0].getTexture(), NULL, 
									   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
								       (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
								       &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
								       (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
									   D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}
		}
		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 1)
			{
				if (gameboard.getPlayer(1)->getGamePiece(i)->getActive())
				{
					world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
											(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
											gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
											gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
											gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
					m_pD3DSprite->SetTransform(&world);
					m_pD3DSprite->Draw(gameboard.getPlayer(1)->getGamePiece(i)->getTexture(), NULL, 
									   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
								       (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
								       &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
								       (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
								       D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}
			else if (gameboard.getActive() == 0)
			{	
				if (gameboard.getPlayer(1)->getGamePiece(i)->getActive())
				{
					world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
											(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
											gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
											gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
											gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
					m_pD3DSprite->SetTransform(&world);
					m_pD3DSprite->Draw(b_sprites[1].getTexture(), NULL, 
									   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
								       (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
								       &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
								       (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
									   D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}
		}
		world = calculateMatrix((initPosition.x * 64), 
								(initPosition.y * 64), 
								g[pieceType].getScalex(),
								g[pieceType].getScaley(),
								g[pieceType].getRotation());
		m_pD3DSprite->SetTransform(&world);
		m_pD3DSprite->Draw(g[pieceType].getTexture(), NULL, 
						   &D3DXVECTOR3((float)(32 + (initPosition.x * 64)), 
						   (float)(32 + (initPosition.y * 64)), 0),
						   &D3DXVECTOR3((float)((initPosition.x * 64) + 32), 
						   (float)((initPosition.y * 64) + 32), 0), 
						   D3DCOLOR_ARGB(255, 255, 255, 255));
		world = calculateMatrix((initPosition.x * 64), 
								(initPosition.y * 64), 
								g[pieceType].getScalex(),
								g[pieceType].getScaley(),
								g[pieceType].getRotation());
		m_pD3DSprite->SetTransform(&world);
		m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, 
						   &D3DXVECTOR3((float)(32 + (initPosition.x * 64)), 
						   (float)(32 + (initPosition.y * 64)), 0),
						   &D3DXVECTOR3((float)((initPosition.x * 64) + 32), 
						   (float)((initPosition.y * 64) + 32), 0), 
						   D3DCOLOR_ARGB(255, 255, 255, 255));
		world = calculateMatrix(640, 0, 
								g[pieceType].getScalex() * 2.5,
								g[pieceType].getScaley() * 2.5,
								g[pieceType].getRotation());
		m_pD3DSprite->SetTransform(&world);
		m_pD3DSprite->Draw(g[pieceType].getTexture(), NULL, 
						   &D3DXVECTOR3((float)(32 + (initPosition.x * 64)), 
						   (float)(32 + (initPosition.y * 64)), 0),
						   &D3DXVECTOR3((float)((initPosition.x * 64) + 32), 
						   (float)((initPosition.y * 64) + 32), 0), 
						   D3DCOLOR_ARGB(255, 255, 255, 255));
		world = calculateMatrix(640, 0, 
								g[pieceType].getScalex() * 2.5,
								g[pieceType].getScaley() * 2.5,
								g[pieceType].getRotation());
		m_pD3DSprite->SetTransform(&world);
		m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, 
						   &D3DXVECTOR3((float)(32 + (initPosition.x * 64)), 
						   (float)(32 + (initPosition.y * 64)), 0),
						   &D3DXVECTOR3((float)((initPosition.x * 64) + 32), 
						   (float)((initPosition.y * 64) + 32), 0), 
						   D3DCOLOR_ARGB(255, 255, 255, 255));

		numFrames += 1.0f;
		timeElapsed += dt;

		m_pD3DSprite->End();
	
		m_pD3DDevice->EndScene();

		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(NULL);

		if (timeElapsed >= 1.0f)
		{
			mFPS = numFrames / dt;
			timeElapsed = 0.0f;
			numFrames = 0.0f;
		}

		wchar_t buffer[64];
		
		swprintf_s(buffer, 64, L"lY: %f", m_MouseState.lY);

		m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		RECT displayclip;
	 	displayclip.top = ((64 * 2) + 30 + 1);
		displayclip.left = (640 + 0 + 1);
		displayclip.bottom = ((64 * 2) + 1 + 30 + 64);
		displayclip.right = 800;

		wchar_t buffer2[64];

		swprintf_s(buffer2, 64, L"%hs", g[pieceType].getName());

		m_classicfont->DrawText(0, buffer2, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pD3DSprite->End();
	
		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
	if ((the_state == PROGRAM) || (the_state == SCOUT))
	{
		float numFrames = 0.0f;
		float timeElapsed = 0.0f;
		float mFPS = 0.0f;

		RECT rect;
		GetWindowRect(hWnd, &rect);
		rect.right = rect.right - rect.left;
		rect.bottom = rect.bottom - rect.top;
		rect.left = 0;
		rect.top = 0;

		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				world = calculateMatrix(i * 64, j * 64, m_sprites[0].getScalex(), 
					                    m_sprites[0].getScaley(), m_sprites[0].getRotation());
				m_pD3DSprite->SetTransform(&world);
				m_pD3DSprite->Draw(m_sprites[0].getTexture(), NULL, &D3DXVECTOR3((float)(32 + (i * 64)), (float)(32 + (j * 64)), 0),
								   &D3DXVECTOR3((float)((i * 64) + 32), (float)((j * 64) + 32), 0), 
							       D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 0)
			{
				if (gameboard.getPlayer(0)->getGamePiece(i)->getActive())
				{
					world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
											(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
											gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
											gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
											gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
					m_pD3DSprite->SetTransform(&world);
					m_pD3DSprite->Draw(gameboard.getPlayer(0)->getGamePiece(i)->getTexture(), NULL, 
									   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
									   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
									   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
									   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										D3DCOLOR_ARGB(255, 255, 255, 255));
					if (gameboard.getPlayer(0)->getGamePiece(i)->getSelection())
					{
						world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
												(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
												gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
												gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
												gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
										   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
										   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
											D3DCOLOR_ARGB(355, 255, 255, 255));
						world = calculateMatrix(640, 0, 
												gameboard.getPlayer(0)->getGamePiece(i)->getScalex() * 2.5,
												gameboard.getPlayer(0)->getGamePiece(i)->getScaley() * 2.5,
												gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(gameboard.getPlayer(0)->getGamePiece(i)->getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
										   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
										   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										   D3DCOLOR_ARGB(255, 255, 255, 255));
						world = calculateMatrix(640, 0, 
												gameboard.getPlayer(0)->getGamePiece(i)->getScalex() * 2.5,
												gameboard.getPlayer(0)->getGamePiece(i)->getScaley() * 2.5,
												gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
										   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
										   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										   D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
			}
			else if (gameboard.getActive() == 1)
			{
				if (gameboard.getPlayer(0)->getGamePiece(i)->getActive())
				{
					if (gameboard.getPlayer(0)->getGamePiece(i)->getShowRank())
					{
						world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
												(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
												gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
												gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
												gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(gameboard.getPlayer(0)->getGamePiece(i)->getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
									       &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
									       (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										    D3DCOLOR_ARGB(255, 255, 255, 255));
					}
					else
					{
						world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
												(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
												gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
												gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
												gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(b_sprites[0].getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
									       (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
									       &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
									       (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										   D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
			}
		}
		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 1)
			{
				if (gameboard.getPlayer(1)->getGamePiece(i)->getActive())
				{
					world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
											(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
											gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
											gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
											gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
					m_pD3DSprite->SetTransform(&world);
					m_pD3DSprite->Draw(gameboard.getPlayer(1)->getGamePiece(i)->getTexture(), NULL, 
									   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
								       (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
								       &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
								       (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
								       D3DCOLOR_ARGB(255, 255, 255, 255));
					if (gameboard.getPlayer(1)->getGamePiece(i)->getSelection())
					{
						world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
					     						(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
						    					gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
							    				gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
								    			gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
						    			   (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
							    	       &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
								           (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
								           D3DCOLOR_ARGB(255, 255, 255, 255));
												world = calculateMatrix(640, 0, 
												gameboard.getPlayer(0)->getGamePiece(i)->getScalex() * 2.5,
												gameboard.getPlayer(0)->getGamePiece(i)->getScaley() * 2.5,
												gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(gameboard.getPlayer(0)->getGamePiece(i)->getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
										   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
										   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										   D3DCOLOR_ARGB(255, 255, 255, 255));
												world = calculateMatrix(640, 0, 
												gameboard.getPlayer(0)->getGamePiece(i)->getScalex() * 2.5,
												gameboard.getPlayer(0)->getGamePiece(i)->getScaley() * 2.5,
												gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(gameboard.getPlayer(0)->getGamePiece(i)->getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
										   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
										   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										   D3DCOLOR_ARGB(255, 255, 255, 255));
						world = calculateMatrix(640, 0, 
												gameboard.getPlayer(1)->getGamePiece(i)->getScalex() * 2.5,
												gameboard.getPlayer(1)->getGamePiece(i)->getScaley() * 2.5,
												gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(gameboard.getPlayer(1)->getGamePiece(i)->getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
										   &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
										   (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										   D3DCOLOR_ARGB(255, 255, 255, 255));
						world = calculateMatrix(640, 0, 
												gameboard.getPlayer(1)->getGamePiece(i)->getScalex() * 2.5,
												gameboard.getPlayer(1)->getGamePiece(i)->getScaley() * 2.5,
												gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
										   &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
										   (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										   D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
			}
			else if (gameboard.getActive() == 0)
			{	
				if (gameboard.getPlayer(1)->getGamePiece(i)->getActive())
				{
					if (gameboard.getPlayer(1)->getGamePiece(i)->getShowRank())
					{
						world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
												(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
												gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
												gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
												gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(gameboard.getPlayer(1)->getGamePiece(i)->getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
										   (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
									       &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
									       (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										    D3DCOLOR_ARGB(255, 255, 255, 255));
					}
					else
					{
						world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
												(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
												gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
												gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
												gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
						m_pD3DSprite->SetTransform(&world);
						m_pD3DSprite->Draw(b_sprites[1].getTexture(), NULL, 
										   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
									       (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
									       &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
									       (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
										   D3DCOLOR_ARGB(255, 255, 255, 255));
					}
				}
			}
		}

		if (the_state == SCOUT)
		{
			for (int i = 0; i < 20; i++)
			{
				world = calculateMatrix((movepositions[i].x * 64), 
										(movepositions[i].y * 64), 
										m_sprites[5].getScalex(),
										m_sprites[5].getScaley(),
										m_sprites[5].getRotation());
				m_pD3DSprite->SetTransform(&world);
				m_pD3DSprite->Draw(m_sprites[5].getTexture(), NULL, 
								   &D3DXVECTOR3((float)(32 + (movepositions[i].x * 64)), 
							       ((float)(32 + (movepositions[i].y * 64))), 0),
							       &D3DXVECTOR3((float)((movepositions[i].x * 64) + 32), 
								   ((float)(movepositions[i].y * 64) + 32), 0), 
								   D3DCOLOR_ARGB(255, 255, 255, 255));

			}
		}
		numFrames += 1.0f;
		timeElapsed += dt;

		if (timeElapsed >= 1.0f)
		{
			mFPS = numFrames / dt;
			timeElapsed = 0.0f;
			numFrames = 0.0f;
		}

		m_pD3DSprite->End();
	
		m_pD3DDevice->EndScene();		
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(NULL);
		wchar_t buffer[64];

		swprintf_s(buffer, 64, L"lY: %f", m_MouseState.lY);

		m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

		wchar_t buffer2[64];

		RECT displayclip;
		displayclip.top = (64 * 2 + 30);
		displayclip.left = (640 + 0 + 1);
		displayclip.bottom = (64 * 2 + 30 + 32);
		displayclip.right = 800;

		LPCSTR s = NULL;

		for (int i = 0 ; i < 40; i++)
		{	
			if ((gameboard.getPlayer(gameboard.getActive())->getGamePiece(i)->getSelection()) && 
				(gameboard.getPlayer(gameboard.getActive())->getGamePiece(i)->getActive()))
			{
				s = gameboard.getPlayer(gameboard.getActive())->getGamePiece(i)->getName();
				swprintf_s(buffer2, 64, L"%hs", gameboard.getPlayer(gameboard.getActive())->getGamePiece(i)->getName());
			}
		}

		if (s != NULL)
		{
			m_classicfont->DrawText(0, buffer2, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		m_pD3DSprite->End();
	
		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	}
	if (the_state == BLANK_BOARD)
	{
		float numFrames = 0.0f;
		float timeElapsed = 0.0f;
		float mFPS = 0.0f;

		RECT rect;
		GetWindowRect(hWnd, &rect);
		rect.right = rect.right - rect.left;
		rect.bottom = rect.bottom - rect.top;
		rect.left = 0;
		rect.top = 0;

		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				world = calculateMatrix(i * 64, j * 64, m_sprites[0].getScalex(), 
					                    m_sprites[0].getScaley(), m_sprites[0].getRotation());
				m_pD3DSprite->SetTransform(&world);
				m_pD3DSprite->Draw(m_sprites[0].getTexture(), NULL, &D3DXVECTOR3((float)(32 + (i * 64)), (float)(32 + (j * 64)), 0),
								   &D3DXVECTOR3((float)((i * 64) + 32), (float)((j * 64) + 32), 0), 
							       D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		for (int i = 0; i < 40; i++)
		{
			world = calculateMatrix((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64), 
									(gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64), 
									gameboard.getPlayer(0)->getGamePiece(i)->getScalex(),
									gameboard.getPlayer(0)->getGamePiece(i)->getScaley(),
									gameboard.getPlayer(0)->getGamePiece(i)->getRotation());
			m_pD3DSprite->SetTransform(&world);
			m_pD3DSprite->Draw(b_sprites[0].getTexture(), NULL, 
							   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64)), 
							   (float)(32 + (gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64)), 0),
							   &D3DXVECTOR3((float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().x * 64) + 32), 
							   (float)((gameboard.getPlayer(0)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
								D3DCOLOR_ARGB(255, 255, 255, 255));
			world = calculateMatrix((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64), 
									(gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64), 
									gameboard.getPlayer(1)->getGamePiece(i)->getScalex(),
									gameboard.getPlayer(1)->getGamePiece(i)->getScaley(),
									gameboard.getPlayer(1)->getGamePiece(i)->getRotation());
			m_pD3DSprite->SetTransform(&world);
			m_pD3DSprite->Draw(b_sprites[1].getTexture(), NULL, 
							   &D3DXVECTOR3((float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64)), 
							   (float)(32 + (gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64)), 0),
							   &D3DXVECTOR3((float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().x * 64) + 32), 
							   (float)((gameboard.getPlayer(1)->getGamePiece(i)->getPosition().y * 64) + 32), 0), 
								D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		/*world = calculateMatrix(200, 200, m_sprites[2].getScalex(), 
					                    m_sprites[2].getScaley(), m_sprites[2].getRotation());
		m_pD3DSprite->SetTransform(&world);
		m_pD3DSprite->Draw(m_sprites[2].getTexture(), NULL, &D3DXVECTOR3((float)(200 + 200), (float)(100 + 200), 0),
								   &D3DXVECTOR3((float)(200 + 200), (float)(100 + 200), 0), 
							       D3DCOLOR_ARGB(255, 255, 255, 255));*/
		m_pD3DSprite->End();

		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

		numFrames += 1.0f;
		timeElapsed += dt;

		if (timeElapsed >= 1.0f)
		{
			mFPS = numFrames / dt;
			timeElapsed = 0.0f;
			numFrames = 0.0f;
		}

		wchar_t buffer[64];

		swprintf_s(buffer, 64, L"lY: %f", m_MouseState.lY);

		m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));

		m_pD3DSprite->End();
	
		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	}
	if (the_state == CREDITS_SCENE)
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		rect.right = rect.right - rect.left;
		rect.bottom = rect.bottom - rect.top;
		rect.left = 0;
		rect.top = 0;

		D3DXMATRIX world;
		// If the device was not created successfully, return
		if(!m_pD3DDevice)
			return;
		
		m_pD3DDevice->BeginScene();
		m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
		
		m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
			
		m_pD3DDevice->BeginScene();

		m_pD3DSprite->Begin(NULL);

		RECT displayclip;
		displayclip.top = 0;
		displayclip.left = 0;
		displayclip.bottom = 640;
		displayclip.right = 800;

		wchar_t buffer[64];
		
		swprintf_s(buffer, 64, L"lY: %f", m_MouseState.lY);

		m_pD3DFont->DrawText(0, buffer, -1, &rect, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		wchar_t buffer2[64];
		
		swprintf_s(buffer, 64, L"%s", L"MADE BY:");

		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		displayclip.top = 75;
		displayclip.left = 75;

		swprintf_s(buffer, 64, L"%s", L"JAMES SORGE");
		
		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		displayclip.top = 150;
		displayclip.left = 0;

		swprintf_s(buffer, 64, L"%s", L"CLASS FOR:");

		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		displayclip.top = 225;
		displayclip.left = 75;

		swprintf_s(buffer, 64, L"%s", L"GSP 361");
		
		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		displayclip.top = 300;
		displayclip.left = 0;

		swprintf_s(buffer, 64, L"%s", L"PROFESSOR:");

		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));

		displayclip.top = 375;
		displayclip.left = 75;

		swprintf_s(buffer, 64, L"%s", L"MICHAEL VAGANOV");
		
		m_pD3DFont2->DrawText(0, buffer, -1, &displayclip, DT_TOP | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 0, 0));
		
		m_pD3DSprite->End();

		m_pD3DDevice->EndScene();
	
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	}

}

void CDirectXFramework::Shutdown()
{
	//*************************************************************************
	// Release COM objects in the opposite order they were created in
	delete [] movepositions;

	for (int i = 0; i < 6; i++)
	{
		m_sprites[i].getTexture()->Release();
	}

	for (int i = 0; i < 2; i++)
	{
		b_sprites[i].getTexture()->Release();
	}

	for (int i = 0; i < 24; i++)
	{
		g[i].getTexture()->Release();
	}

	system->release();
	
	m_Mouse->Release();

	m_Keyboard->Release();

	m_DInput->Release();
	
	// Sprite
	m_pD3DSprite->Release();
	// Font
	m_pD3DFont->Release();
	// 3DDevice	
	m_pD3DDevice->Release();	
	// 3DObject
	m_pD3DObject->Release();

	CoUninitialize();
	//*************************************************************************

}

D3DXMATRIX & calculateMatrix(int x, int y, float scalex, float scaley, float angle)
{
	D3DXMATRIX scale, rot, trans, world;
	
	D3DXMatrixIdentity(&trans);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rot);
	D3DXMatrixIdentity(&world);
	D3DXMatrixRotationZ(&rot, D3DXToRadian(angle));
	D3DXMatrixTranslation(&trans, x, y, 0);
	D3DXMatrixScaling(&scale, scalex, scaley, 0);
	world = rot * scale * trans;
	return world;	
}

bool CDirectXFramework::keyDown(BYTE buffer[], float dt)
{
	
	//press right

	if (buffer[DIK_RIGHT] & 0x80 && !pressed[DIK_RIGHT])
	{
		GamePiece * g = NULL;
		
		//get Selected Game Piece

		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 0)
			{
				if (gameboard.getPlayer(0)->getGamePiece(i)->getSelection())
				{
					g = gameboard.getPlayer(0)->getGamePiece(i);
				}
			}
			if (gameboard.getActive() == 1)
			{
				if (gameboard.getPlayer(1)->getGamePiece(i)->getSelection())
				{
					g = gameboard.getPlayer(1)->getGamePiece(i);
				}
			}
		}

		//if null kick out of function

		if (g == NULL)
		{
			return false;
		}
		int options = MessageBox(NULL, L"Do You Wish to Move Piece Right?", L"", MB_YESNO);
		
		//if say no then set selection boxes to false
		
		if (options == IDNO)
		{
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			return false;
		}
		
		//move piece
		
		if (gameboard.move(g, D3DXVECTOR3(g->getPosition().x + 1.0f, g->getPosition().y, 0.0f)))
		{
			
			//set selection to false
			
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			if (gameboard.getActive() == 0)
			{
				gameboard.setActive(1);
			}
			else if (gameboard.getActive() == 1)
			{
				gameboard.setActive(0);
			}
		}
		else
		{
			
			//Invalid move
			
			pressed[DIK_RIGHT] = true;
			MessageBox(NULL, L"Invalid Move", L"", MB_OK);
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			return false;
		}
		pressed[DIK_RIGHT] = true;
		return true;
	}
	else
	{
		//if pressed reset key
		
		if (buffer[DIK_RIGHT] & 0x80)
		{}
		else
		{
			pressed[DIK_RIGHT] = false;
		}
	}

	//press left

	if (buffer[DIK_LEFT] & 0x80 && !pressed[DIK_LEFT])
	{
		//get Selected Game Piece
		
		GamePiece * g = NULL;
		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 0)
			{
				if (gameboard.getPlayer(0)->getGamePiece(i)->getSelection())
				{
					g = gameboard.getPlayer(0)->getGamePiece(i);
				}
			}
			if (gameboard.getActive() == 1)
			{
				if (gameboard.getPlayer(1)->getGamePiece(i)->getSelection())
				{
					g = gameboard.getPlayer(1)->getGamePiece(i);
				}
			}
		}
		
		//if null kick out of function
		
		if (g == NULL)
		{
			return false;
		}
		int options = MessageBox(NULL, L"Do You Wish to Move Piece Left?", L"", MB_YESNO);
		
		//if click no set all selections to false
		
		if (options == IDNO)
		{
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			return false;
		}
		
		//move piece
		
		if(gameboard.move(g, D3DXVECTOR3(g->getPosition().x - 1.0f, g->getPosition().y, 0.0f)))
		{
			
			//set all selections to false

			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			if (gameboard.getActive() == 0)
			{
				gameboard.setActive(1);
			}
			else if (gameboard.getActive() == 1)
			{
				gameboard.setActive(0);
			}

		}
		else
		{
			
			//invalid move
			
			pressed[DIK_LEFT] = true;
			MessageBox(NULL, L"Invalid Move", L"", MB_OK);
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			return false;
		}
		pressed[DIK_LEFT] = true;
		return true;
	}
	else
	{
		//if pressed reset key
		
		if (buffer[DIK_LEFT] & 0x80)
		{}
		else
		{
			pressed[DIK_LEFT] = false;
		}
	}
	
	//press down
	
	if (buffer[DIK_DOWN] & 0x80 && !pressed[DIK_DOWN])
	{
		
		//get Selected Game Piece

		GamePiece * g = NULL;
		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 0)
			{
				if (gameboard.getPlayer(0)->getGamePiece(i)->getSelection())
				{
					g = gameboard.getPlayer(0)->getGamePiece(i);
				}
			}
			if (gameboard.getActive() == 1)
			{
				if (gameboard.getPlayer(1)->getGamePiece(i)->getSelection())
				{
					g = gameboard.getPlayer(1)->getGamePiece(i);
				}
			}
		}
		
		//if null kick out of function

		if (g == NULL)
		{
			return false;
		}
		int options = MessageBox(NULL, L"Do You Wish to Move Piece Down?", L"", MB_YESNO);
		
		//if no set all selections to false
		
		if (options == IDNO)
		{
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			return false;
		}
		
		//move piece

		if(gameboard.move(g, D3DXVECTOR3(g->getPosition().x, g->getPosition().y + 1.0f, 0.0f)))
		{
			
			//set all selections to false
			
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			if (gameboard.getActive() == 0)
			{
				gameboard.setActive(1);
			}
			else if (gameboard.getActive() == 1)
			{
				gameboard.setActive(0);
			}
		}
		else
		{
			//Invalid Move
			
			pressed[DIK_DOWN] = true;
			MessageBox(NULL, L"Invalid Move", L"", MB_OK);
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			return false;
		}
		pressed[DIK_DOWN] = true;
		return true;
	}
	else
	{
		//if pressed reset key
		
		if (buffer[DIK_DOWN] & 0x80)
		{}
		else
		{
			pressed[DIK_DOWN] = false;
		}
	}

	//move up

	if (buffer[DIK_UP] & 0x80 && !pressed[DIK_UP])
	{
		//Get Selected Piece
		
		GamePiece * g = NULL;
		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 0)
			{
				if (gameboard.getPlayer(0)->getGamePiece(i)->getSelection())
				{
					g = gameboard.getPlayer(0)->getGamePiece(i);
				}
			}
			if (gameboard.getActive() == 1)
			{
				if (gameboard.getPlayer(1)->getGamePiece(i)->getSelection())
				{
					g = gameboard.getPlayer(1)->getGamePiece(i);
				}
			}
		}
		
		//if null kick out of function

		if (g == NULL)
		{
			return false;
		}
		int options = MessageBox(NULL, L"Do You Wish to Move Piece Up?", L"", MB_YESNO);

		//if no set all selection boxes to false
		if (options == IDNO)
		{
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			return false;
		}

		//move piece

		if(gameboard.move(g, D3DXVECTOR3(g->getPosition().x, g->getPosition().y - 1.0f, 0.0f)))
		{
		  
			//set all selection boxes to false
			
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			if (gameboard.getActive() == 0)
			{
				gameboard.setActive(1);
			}
			else if (gameboard.getActive() == 1)
			{
				gameboard.setActive(0);
			}
		}
		else
		{
			//invalid move
			
			pressed[DIK_UP] = true;
			MessageBox(NULL, L"Invalid Move", L"", MB_OK);
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
				}
				if (gameboard.getActive() == 1)
				{
					gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
				}
			}
			return false;
		}
		pressed[DIK_UP] = true;
		return true;
	}
	else
	{
		//press key resetter
		
		if (buffer[DIK_UP] & 0x80)
		{}
		else
		{
			pressed[DIK_UP] = false;
		}
	}
	return false;
}

bool CDirectXFramework::keyDown2(BYTE buffer[], GamePiece g, int & piece, D3DXVECTOR3 & p, float dt)
{
	//move right
	
	if (buffer[DIK_RIGHT] & 0x80 && !pressed[DIK_RIGHT])
	{
		if (!pressed[DIK_RIGHT])
		{
			if (p.x >= 9.0)
			{
				pressed[DIK_RIGHT] = true;
				return false;
			}
			else
			{
				pressed[DIK_RIGHT] = true;
				p.x = p.x + 1.0f;
				return true;
			}
		}
	}
	else
	{
		
		//press key resetter
		
		if (buffer[DIK_RIGHT] & 0x80)
		{}
		else
		{
			pressed[DIK_RIGHT] = false;
		}
	}

	//move left

	if (buffer[DIK_LEFT] & 0x80 && !pressed[DIK_LEFT])
	{
		if (!pressed[DIK_LEFT])
		{
			if (p.x <= 0.0)
			{
				pressed[DIK_LEFT] = true;
				return false;
			}
			else
			{
				pressed[DIK_LEFT] = true;
				p.x = p.x - 1.0f;
				return true;
			}
		}
	}
	else
	{

		//press key resetter

		if (buffer[DIK_LEFT] & 0x80)
		{}
		else
		{
			pressed[DIK_LEFT] = false;
		}
	}	

	//move up

	if (buffer[DIK_UP] & 0x80 && !pressed[DIK_UP])
	{
		if (!pressed[DIK_UP])
		{
			if ((gameboard.getActive() == 0) && (p.y <= 6.0))
			{
				pressed[DIK_UP] = true;
				return false;
			}
			else if ((gameboard.getActive() == 1) && (p.y <= 0.0))
			{
				pressed[DIK_UP] = true;
				return false;
			}
			else
			{
				pressed[DIK_UP] = true;
				p.y = p.y - 1.0f;
				return true;
			}
		}
	}
	else
	{
	
		//press key resetter
		
		if (buffer[DIK_UP] & 0x80)
		{}
		else
		{
			pressed[DIK_UP] = false;
		}
	}

	//move down

	if (buffer[DIK_DOWN] & 0x80 && !pressed[DIK_DOWN])
	{
		if (!pressed[DIK_DOWN])
		{
			if ((gameboard.getActive() == 0) && (p.y >= 9.0))
			{
				pressed[DIK_DOWN] = true;
				return false;
			}
			else if ((gameboard.getActive() == 1) && (p.y >= 3.0))
			{
				pressed[DIK_DOWN] = true;
				return false;
			}
			else
			{
				pressed[DIK_DOWN] = true;
				p.y = p.y + 1.0f;
				return true;
			}
		}
	}
	else
	{
	
		//press key resetter
		
		if (buffer[DIK_DOWN] & 0x80)
		{}
		else
		{
			pressed[DIK_DOWN] = false;
		}
	}

	//Enter confirmation
	if (buffer[DIK_RETURN] & 0x80 && !pressed[DIK_RETURN])
	{
		if (!pressed[DIK_RETURN])
		{
			if (gameboard.checkForCollision2(p))
			{
				pressed[DIK_RETURN] = true;
				return false;
			}
			else
			{
				gameboard.getPlayer(gameboard.getActive())->getGamePiece(piece)->setRank(g.getRank());
				gameboard.getPlayer(gameboard.getActive())->getGamePiece(piece)->setTexture(g.getTexture());
				gameboard.getPlayer(gameboard.getActive())->getGamePiece(piece)->setScalex(g.getScalex());
				gameboard.getPlayer(gameboard.getActive())->getGamePiece(piece)->setScaley(g.getScaley());
				gameboard.getPlayer(gameboard.getActive())->getGamePiece(piece)->setRotation(g.getRotation());
				gameboard.getPlayer(gameboard.getActive())->getGamePiece(piece)->setActive(true);
				gameboard.getPlayer(gameboard.getActive())->getGamePiece(piece)->setPlayerCode(gameboard.getActive());
				gameboard.getPlayer(gameboard.getActive())->getGamePiece(piece)->setPosition(p);
				pressed[DIK_RETURN] = true;
				piece++;
				return true;
			}
		}
	}
	else
	{

		//press key resetter

		if (buffer[DIK_RETURN] & 0x80)
		{}
		else
		{
			pressed[DIK_RETURN] = false;
		}
	}
	return false;
}

bool CDirectXFramework::keyDown3(BYTE buffer[], float dt)
{
	//Enter Selection
	
	if (buffer[DIK_RETURN] & 0x80 && !pressed[DIK_RETURN])
	{
		if (!pressed[DIK_RETURN])
		{
			pressed[DIK_RETURN] = true;
			if (gameboard.getActive() == 1)
			{
				the_state = INIT;
			}
			else if (gameboard.getActive() == 0)
			{
				the_state = PROGRAM;
			}
		}
	}
	else
	{
		
		//key resetter

		if (buffer[DIK_RETURN] & 0x80)
		{
		}
		else
		{
			pressed[DIK_RETURN] = false;
			return true;
		}
	}
	return false;
}

bool CDirectXFramework::keyDown4(BYTE buffer[], float dt)
{
	
	//up for menu
	
	if ((menuyposition > 250) && !pressed[DIK_UP])
	{
		if (buffer[DIK_UP] & 0x80)
		{
			menuyposition -= 75;
			pressed[DIK_UP] = true;
		}
	}
	else 
	{

		//key resetter

		if (buffer[DIK_UP] & 0x80)
		{}
		else
		{
			pressed[DIK_UP] = false;
		}
	}
	
	//press down on menu

	if ((menuyposition < 400) && !(pressed[DIK_DOWN]))
	{
		if (buffer[DIK_DOWN] & 0x80)
		{
			menuyposition += 75;
			pressed[DIK_DOWN] = true;
		}
	}
	else
	{
	
		//key resetter

		if (buffer[DIK_DOWN] & 0x80)
		{}
		else
		{
			pressed[DIK_DOWN] = false;
		}
	}

	//Enter Selection

	if (!pressed[DIK_RETURN])
	{
		if ((menuyposition == 250) && (buffer[DIK_RETURN] & 0x80))
		{
			the_state = INIT;
			//channel[1]->stop();
			pressed[DIK_RETURN] = true;
		}
		if ((menuyposition == 325) && (buffer[DIK_RETURN] & 0x80))
		{
			the_state = CREDITS_SCENE;
			pressed[DIK_RETURN] = true;
		}
		if ((menuyposition == 400) && (buffer[DIK_RETURN] & 0x80))
		{
			the_state = QUIT;
		}
	}
	else
	{
	
		//key resetter

		if (buffer[DIK_RETURN] & 0x80)
		{}
		else
		{
			pressed[DIK_RETURN] = false;
		}
	}
	return true;
}


bool CDirectXFramework::mouseDown()
{
	//left mouse button normally
	
	if ((m_MouseState.rgbButtons[0] & 0x80) && !mousePressed[0])
	{
		if (m_MouseState.rgbButtons[0] & 0x80)
		{
			RECT rect;
			GetWindowRect(m_hWnd, &rect);
			POINT p;
			GetCursorPos(&p);
			D3DXVECTOR3 l_position = D3DXVECTOR3((float)((p.x - rect.left - 8)/ 64), (float)((p.y - rect.top - 26)/ 64), 0.0f);
			gameboard.makeSelection(l_position);
			mousePressed[0] = true;
		}
	}
	else 
	{
		
		//mouse reset
		
		if (m_MouseState.rgbButtons[0] & 0x80)
		{}
		else
		{
			mousePressed[0] = false;
		}
	}
	return true;
};

bool CDirectXFramework::keyDown5(BYTE buffer[], float dt)
{
	
	//credits scene entering
	
	if (!pressed[DIK_RETURN])
	{
		if (buffer[DIK_RETURN] & 0x80)
		{
			pressed[DIK_RETURN] = true;
			the_state = MENU;
		}
	}	
	else
	{
		if (buffer[DIK_RETURN] & 0x80)
		{}
		else
		{
			pressed[DIK_RETURN] = false;
		}
	}
	return true;
}
bool CDirectXFramework::mouseDown2()
{
	
	//left mouse button press on mouse interface
	
	if ((m_MouseState.rgbButtons[0] & 0x80) && !mousePressed[0])
	{
		if (m_MouseState.rgbButtons[0] & 0x80)
		{
			RECT rect;
			GetWindowRect(m_hWnd, &rect);
			POINT p;
			GetCursorPos(&p);
			D3DXVECTOR3 l_position = D3DXVECTOR3((float)((p.x - rect.left - 8)/ 64), (float)((p.y - rect.top - 26)/ 64), 0.0f);
			bool checker = false;
			for (int i = 0; i < 20; i++)
			{
				if (l_position == movepositions[i])
				{
					checker = true;
					i = 20;
				}
			}
			if (!checker)
			{
				return false;
			}
			GamePiece * g = NULL;
			for (int i = 0; i < 40; i++)
			{
				if (gameboard.getActive() == 0)
				{
					if (gameboard.getPlayer(0)->getGamePiece(i)->getSelection())
					{
						g = gameboard.getPlayer(0)->getGamePiece(i);
					}
				}
				if (gameboard.getActive() == 1)
				{
					if (gameboard.getPlayer(1)->getGamePiece(i)->getSelection())
					{
						g = gameboard.getPlayer(1)->getGamePiece(i);
					}
				}
			}
			if(gameboard.move(g, l_position))
			{
				mousePressed[0] = true;
				the_state = PROGRAM;
				for (int i = 0; i < 40; i++)
				{
					if (gameboard.getActive() == 0)
					{
						gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
					}
					if (gameboard.getActive() == 1)
					{
						gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
					}
				}
				if (gameboard.getActive() == 0)
				{
					gameboard.setActive(1);
				}
				else if (gameboard.getActive() == 1)
				{
					gameboard.setActive(0);
				}
				else
				{
					MessageBox(NULL, L"Invalid Move", L"", MB_OK);
					for (int i = 0; i < 40; i++)
					{
						if (gameboard.getActive() == 0)
						{
							gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
						}
						if (gameboard.getActive() == 1)
						{
							gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
						}
					}
					return false;
				}
			}
		}
	}
	else 
	{

		//mouse button resetter

		if (m_MouseState.rgbButtons[0] & 0x80)
		{}
		else
		{
			mousePressed[0] = false;
		}
	}
	
	//right mouse button cancel selections
	
	if (m_MouseState.rgbButtons[1] & 0x80)
	{
		the_state = PROGRAM;
		for (int i = 0; i < 40; i++)
		{
			if (gameboard.getActive() == 0)
			{
				gameboard.getPlayer(0)->getGamePiece(i)->setSelection(false);
			}
			if (gameboard.getActive() == 1)
			{
				gameboard.getPlayer(1)->getGamePiece(i)->setSelection(false);
			}
		}
	}
	else
	{
		
		//mouse button resetter
		
		if (m_MouseState.rgbButtons[0] & 0x80)
		{}
		else
		{
			mousePressed[0] = false;
		}
	}
	return true;
}

