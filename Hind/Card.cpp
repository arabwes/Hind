
#include "Card.h"

Card::Card(string tFName, string tName, string tSuit, int tVal, int tNum, string tFile, string tFacedown)
{
	fullName = tFName;	//Full name of card. (ie. Ace of Spade)
	name = tName;		//Name of card such as King or 5
	suit = tSuit;		//Suit of card such as Club
	value = tVal;		//Value of card (Ace can be 1 or 11 points in Blackjack)
	number = tNum;		//Number of card to help find filename
	selected = false;		//Flag to tell if card is selected
	fileName = tFile;	//Filename for card image
	facedownFileName = tFacedown; 
	faceDown = true;
	Texture = LoadTexture(facedownFileName, TransColor);
	
	//Coordinates of card's position
	x = 0;
	y = 0;
	//Definition of sprite sheet
	NumCol = 1;
	FrameW = 71;
	FrameH = 96;
	Delay = 135;
	ScaleX = 1;
	ScaleY = 1;
	SetStart(0); 
	SetEnd(0);
	SetDirection(1);
}

Card::~Card()
{
	
}

//Update which face the card is facing
void Card::UpdateFace(bool ShowFace)
{
	if(ShowFace)
		Texture = LoadTexture(fileName, TransColor);
	else
		Texture = LoadTexture(facedownFileName, TransColor);
}

//Reposition card to new coordinates
void Card::Reposition(float X, float Y)
{
	x = X;
	y = Y;
}

//Get Functions
int Card::GetValue()
{
	return value;
}

string Card::GetSuit()
{
	return suit;
}

string Card::GetFullName()
{
	return fullName;
}
string Card::GetName()
{
	return Name;
}
int Card::GetNum()
{
	return number;
}
