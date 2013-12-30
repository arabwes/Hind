#ifndef CARD_H
#define CARD_H
//Card.h
//Basic Outline of a Playing Card

#include <stack>
#include "Sprite.h"

class Card : public Sprite
{
private:
	string fullName;			//Full name of card (ie.. Ace of Spades)
	string name;				//Name of card (ie.. King, Ace, 10)
	int value;					//Numerical value of card (King is 10)
	int number;					//Numerical order of card
	string suit;				//Suit of card
	string fileName;			//Filename of Card image
	string facedownFileName;	//Filename of back of card
	bool faceDown;				//Flag for the direction the card is facing


public:
	bool selected;			//Flag to recognize if a card has been selected or not
	int GetValue();			//Returns Value of card
	int GetNum();			//Returns Number of card
	string GetSuit();		//Returns Suit of card
	string GetName();		//Returns Name of card
	string GetFullName();	//Returns FullName of card
	void UpdateFace(bool ShowFace);		//Updates which direction the card is facing
	void Reposition(float x, float y);	//Repositions card to new coordinates
	Card();
	Card(string tFName, string tName, string tSuit, int tVal, int tNum, string File, string facedown);  //Creates Card
	~Card();
};

#endif