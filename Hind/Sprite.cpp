#include "Sprite.h"

//Return X value
float Sprite::GetX()
{
	return x;
}

//Return Y Value
float Sprite::GetY()
{
	return y;
}

float Sprite::GetScaleX()
{
	return scaleX;
}

float Sprite::GetScaleY()	
{
	return scaleY;
}

int Sprite::GetFrameW()	
{
	return frameW;
}

int Sprite::GetFrameH()
{
	return frameH;
}
string Sprite::GetName()
{
	return Name;
}
int Sprite::GetDirection()
{
	return direction;
}

bool Sprite::GetDeleteMe()
{
	return deleteMe;
}

//Set the Start frame of Animation
void Sprite::SetStart(int frame)
{
	startFrame = frame;
}

//Set the End frame of Animation
void Sprite::SetEnd(int frame)
{
	endFrame = frame;
}

//Setdelay between Animation
void Sprite::SetDelay(int MilSec)
{
	delay = MilSec;
}

//Set Direction to go through sprite sheet
void Sprite::SetDirection(int Dir)
{
	direction = Dir;
}

void Sprite::SetDeletion(bool Del)
{
	deleteMe = Del;
}
//Draw specific frame of Animation to the buffer
void Sprite::DrawFrame()
{
	//Current Pos of sprite
	D3DXVECTOR3 pos(x, y, 0);

	//Declare a rect that stores the size of each frame of a sprite sheet
	RECT rect;
	rect.left = (curFrame % numCol) * frameW;
	rect.right = rect.left + frameW;
	rect.top = (curFrame / numCol) * frameH;
	rect.bottom = rect.top + frameH;

	spriteobj->Draw(Texture, &rect, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));
}

void Sprite::TransformDraw(int rot)
{
	//Create scale vector
	D3DXVECTOR2 scale (scaleX, scaleY);

	//Get center of sprite
	D3DXVECTOR2 center ((float)(frameW * scaleX) / 2.0f, (float)(frameH * scaleY) / 2.0f);

	//Translation vector
	D3DXVECTOR2 trans (x, y);

	//Create 2D transformation matrix
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, &scale, &center, rot, &trans);

	//Tell sprite to us the transformation
	spriteobj->SetTransform(&mat);

	//Declare a rect that stores the size of each frame of a sprite sheet
	RECT rect;
	rect.left = (curFrame % numCol) * frameW;
	rect.right = rect.left + frameW;
	rect.top = (curFrame / numCol) * frameH;
	rect.bottom = rect.top + frameH;

	spriteobj->Draw(Texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

//Set the current frame to Animate the sprite 
void Sprite::SpriteAnimate()
{
	if((int)GetTickCount() > sT +delay)
	{
		sT = GetTickCount();

		curFrame += direction;

		if(curFrame > endFrame)
			curFrame = startFrame;

		if(curFrame < startFrame)
			curFrame = startFrame;
	}
}

//Used in constuctor to set Texture value
LPDIRECT3DTEXTURE9 Sprite::LoadTexture(std::string filename, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;

	//Get width and height from bitmap file
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);

	if(result != D3D_OK)
		return NULL;

	//Create the new texture by loading a bitmap image file
	D3DXCreateTextureFromFileEx(
		d3ddev,				//Direct3D device obj
		filename.c_str(),	//Filename of bitmap
		info.Width,			//Bitmap image width
		info.Height,		//Bitmap image height
		1,					//Mip-map levels (1 for no chain)
		D3DPOOL_DEFAULT,	//The type of surface (standard)
		D3DFMT_UNKNOWN,		//Surface format (default)
		D3DPOOL_DEFAULT,	//Memory class for textures
		D3DX_DEFAULT,		//Image filter
		D3DX_DEFAULT,		//Mip filter
		transcolor,			//Color key for transparency (Alpha)
		&info,				//Bitmap file info (loaded from file earlier)
		NULL,				//Color palette
		&texture);			//Dest texture

	if(result != D3D_OK)
		return NULL;

	return texture;
}

//Increment functions
void Sprite::IncrementX(int w)
{
	x+=w;
}
void Sprite::IncrementY(int h)
{
	y+=h;
}


//TORS
Sprite::Sprite()
{

}

Sprite::Sprite(std::string FILENAME, std::string NAME, D3DCOLOR TransColor, float DesiredX, float DesiredY,
	int NumOfCol, int frameWi, int frameHe, float SCX, float SCY)
{
	//SET PARAMS
	Texture = LoadTexture(FILENAME, TransColor);

	x = DesiredX;
	y = DesiredY;

	numCol = NumOfCol;
	frameW = frameWi;
	frameH = frameHe;

	delay = 135;

	scaleX = SCX;
	scaleY = SCY;
}

Sprite::~Sprite()
{
	Texture->Release();
}