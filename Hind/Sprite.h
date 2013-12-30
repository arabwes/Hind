#ifndef SPRITE_H
#define SPRITE_H

#include "MyDirectX.h"

class Sprite
{
protected:

	//GENERAL PURPOSE
	float x, y, v;				//X pos, Y Pos, Velocity
	D3DCOLOR TransColor;		//Transparency Color
	LPDIRECT3DTEXTURE9 Texture;	//Texture used for Sprite
	std::string Name;

	//FOR ANIMATION
	float	scaleX;
	float	scaleY;
	int		numCol;		//Number of Columns in the sprite   
	int		curFrame;	//Current Frame
	int		startFrame;	//Start frame
	int		endFrame;	//End Frame
	int		frameW;		//Width of each frame of animation
	int		frameH;		//Height of each frame of animation
	int		delay;		//Delay between animations
	int		sT;			//Start time (Used to animate)
	int		direction;	//Direction you want to animate through a sprite sheet
	bool	deleteMe;
						//Positive numbers move forward X frames per call
						//Negative numbers move backwards X frames per call
						///CurFrame += Direction

public:
	float GetX();				//Return X
	float GetY();				//Return Y
	float GetScaleX();			//Return ScaleX
	float GetScaleY();			//Return ScaleY
	int GetFrameW();			//Return frame width
	int GetFrameH();			//Return frame height
	int GetDirection();			//Return Direction
	bool GetDeleteMe();
	string GetName();			//Returns name

	void SetStart(int frame);	//Set the Start frame
	void SetEnd(int frame);		//Set the End frame
	void SetDelay(int MilSec);	//Set Delay between animation
	void SetDirection(int Dir);	//Set Direction to cycle through sprite sheet
	void SetDeletion(bool Del);

	void IncrementX(int s);		//increments X by s
	void IncrementY(int h);		//increments Y by h


	void DrawFrame();			//Draw specific frame of sprite sheet to backbuffer
	void TransformDraw(int		//
		rot);
	void SpriteAnimate();		//Change CurrentFrame to animate through sprite sheet

	LPDIRECT3DTEXTURE9 LoadTexture(std::string filename, 
		D3DCOLOR transcolor); //Texture of object
	
	Sprite();
	Sprite(std::string FILENAME, std::string NAME, D3DCOLOR TransColor, float DesiredX, float DesiredY, 
		int NumCol, int FrameW, int FrameH, float SCX, float SCY);
	~Sprite();
};

#endif