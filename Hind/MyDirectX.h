/*  Beginning Game Programming, Third Edition
    MyDirectX.h

    Changes during AR:
        return value of Key_Down
*/

#pragma once

//header files
#define WIN32_EXTRA_LEAN
#define DIRECTINPUT_VERSION 0x0800
#define  _USE_MATH_DEFINES
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <xinput.h>
#include <math.h>
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
//libraries
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//program values
extern const std::string APPTITLE;
extern const int SCREENW;
extern const int SCREENH;
extern bool gameover;

//macro to detect key presses
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//Direct3D objects
extern LPDIRECT3D9 d3d; 
extern LPDIRECT3DDEVICE9 d3ddev; 
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPD3DXSPRITE spriteobj;


//Direct3D functions
bool Direct3D_Init(HWND hwnd, int width, int height, bool fullscreen);

//Wrapper function that releases memory
void Direct3D_Shutdown();

//Wrappr function that loads surfaces
LPDIRECT3DSURFACE9 LoadSurface(std::string filename);

//Wrapper function that renders surfaces
void DrawSurface(LPDIRECT3DSURFACE9 dest, float x, float y, LPDIRECT3DSURFACE9 source);

//Wrapper function that loads textures
LPDIRECT3DTEXTURE9 LoadTexture(std::string filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));

//Wrapper function that sets the current frame to animate
void Sprite_Draw_Frame(LPDIRECT3DTEXTURE9 tex, int destx, int desty, int framenum, int framew, int frameh, int col);

//Wrapper function that cycles through the sprite sheet to replicate animation
void Sprite_Animate(int &frame, int startframe, int endframe, int direction, int &starttime, int delay);


//DirectInput objects, devices, and states
//edited
extern LPDIRECTINPUT8 dinput;
//extern IDirectInput8* dinput;

//edited
extern LPDIRECTINPUTDEVICE8 dimouse;
//extern IDirectInputDevice8* dimouse;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
//extern IDirectInputDevice8* dikeyboard;

extern DIMOUSESTATE mouse_state;
extern XINPUT_GAMEPAD controllers[4];

//DirectInput functions
bool DirectInput_Init(HWND);
void DirectInput_Update();
void DirectInput_Shutdown();

//CHANGED in ch6
bool Key_Down(int);

int Mouse_Button(int);
int Mouse_X();
int Mouse_Y();
void XInput_Vibrate(int contNum = 0, int amount = 65535);
bool XInput_Controller_Found();

//game functions
bool Game_Init(HWND window);
void Game_Run(HWND window);
void Game_End();

//font functions
LPD3DXFONT MakeFont(string name, int size);
void FontPrint(LPD3DXFONT font, int x, int y, string text, D3DCOLOR color = D3DCOLOR_XRGB(255,255,255));

//*** ADDED 
extern LPD3DXSPRITE spriteobj;

//Additional functions
void ConcatenateString(string &tString, string Letter, int Number);
void ConcatenateString(string &tString,string Letter1, string Letter2, int Number);
