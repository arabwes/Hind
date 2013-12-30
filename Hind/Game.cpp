/*
CreateDeck - Creates and combines 2 decks (red/blue) - Works!
players are created and have hands


*/
//Header files
#include "MyDirectX.h"
#include "Sprite.h"
#include "Field.h"
#include "Player.h"
#include <sstream>
#include "ScrollingBG.h"
using namespace std;

//Functions
void GameLogic();
void GameDraw();

//Change these as needed
const std::string APPTITLE = "Hind";
const int SCREENW = 1024;
const int SCREENH = 768;
const int BUFFERW = SCREENW * 2;
const int BUFFERH = SCREENH * 2;
LPDIRECT3DSURFACE9 background = NULL;			//background object
LPD3DXFONT font;								//font object

//Includes
#include <vector>

//Pointers to objects
Sprite* ptrToSprite = NULL;

//Objects
Field *gameField;
//Player *players[0], *players[1];

//Vectors(And their iterators) of pointers to objects
Player* players[2];
std::vector<Sprite*>sVect;
std::vector<Sprite*>::iterator sIt;

//Surfaces and Textures
LPDIRECT3DTEXTURE9 drawButton;
LPDIRECT3DTEXTURE9 discardButton;
LPDIRECT3DTEXTURE9 dropButton;

//vector positions for Control buttons
D3DXVECTOR3 drawCoord(900, 284, 0);
D3DXVECTOR3 discardCoord(900, 359, 0);
D3DXVECTOR3 dropCoord(900, 434, 0);

//Time Variables
float Timer, ST;


bool Game_Init(HWND window)
{
	//Seed random number generator
	srand(time(NULL));
	//For MP3
	CoInitialize(0);
	
    //initialize Direct3D
    Direct3D_Init(window, SCREENW, SCREENH, false);
    //initialize DirectInput
    DirectInput_Init(window);

	//Get the back buffer surface
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	//Init surfaces, textures, and objects here
	drawButton = LoadTexture("DrawButton.jpg", NULL);
	dropButton = LoadTexture("DropButton.jpg", NULL);
	discardButton = LoadTexture("DiscardButton.jpg", NULL);

	//Create players
	
	players[0] = new Player("Wasim", 600);
	players[1] = new Player("Nasir", 80);

	//Create gameField and Deck
	gameField = new Field();
	gameField->CreateDeck();
	
	//Give each player a hand of 14 cards
	for(int i = 1; i <= 14; i++)
	{
		players[0]->DrawCard(gameField->Draw());
		players[1]->DrawCard(gameField->Draw());
	}
	//Randomly choose who gets to play first and give that player first draw
	int t = rand()%2;
	players[t]->turn = true;
	players[t]->DrawCard(gameField->Draw());

	//create a font
	font = MakeFont("Arial", 24);

	//Set Timer
	Timer = 10;

	//create background
	HRESULT result = 
		d3ddev->CreateOffscreenPlainSurface(
		BUFFERW,
		BUFFERH,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&background,
		NULL);
	if(result != D3D_OK) return false;

	//load background
	background = LoadSurface("CardTable.jpg");
	if(!background) return false;

	return true;
}

void Game_Run(HWND window)
{
    //make sure the Direct3D device is valid
	if (!d3ddev) return;
	//update input devices
	DirectInput_Update();
	//Clear the screen to blue
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);

	//Game Logic goes Here
	GameLogic();

	//start rendering
	if (d3ddev->BeginScene())
	{
		d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);

		//Draw here
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);


		GameDraw();

		spriteobj->End();

		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
			
	}
	//to exit
	if (KEY_DOWN(VK_ESCAPE))
		gameover = true;
}

void Game_End()
{
	//Deallocate memory here
	for(sIt = sVect.begin(); sIt != sVect.end(); sIt++)
	{
		delete (*sIt);
	}
	background->Release();
	font->Release();

	DirectInput_Shutdown();
	Direct3D_Shutdown();

}

void GameLogic()
{
	for(int i = 0; i <= 1; i++)
	{

		if(players[i]->turn)
		{
			//Do everthing for turn here
			
			if(GetTickCount() > ST + 10000)
			{
				ST = GetTickCount();
				//At the end, switch turn to other player

				if(i == 0)
				{
					players[0]->turn = false;
					players[1]->turn = true;
				}

				else if(i == 1)
				{
					players[0]->turn = true;
					players[1]->turn = false;
				}
			}
			players[i]->UpdateHand();
			
		}
	}
}

void GameDraw()
{
	spriteobj->Draw(drawButton, NULL, NULL, &drawCoord, D3DCOLOR_XRGB(255, 255, 255));
	spriteobj->Draw(discardButton, NULL, NULL, &discardCoord, D3DCOLOR_XRGB(255, 255, 255));
	spriteobj->Draw(dropButton, NULL, NULL, &dropCoord, D3DCOLOR_XRGB(255, 255, 255));

	players[0]->ShowHand();
	players[1]->ShowHand();

	gameField->deck.top()->SpriteAnimate();
	gameField->deck.top()->DrawFrame();
		
}