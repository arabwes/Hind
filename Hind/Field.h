#ifndef FIELD_H
#define FIELD_H
//Field.h
//The field is where the deck is and where cards are exchanged

#include <vector>
#include <algorithm>
#include "Card.h"

class Field
{
private:
	Card* cardList[104];	//List of all cards

public:
	stack<Card*> deck;			//Deck of all cards
	stack<Card*> discardPile;	//Discard pile
	//Drop zones for respective players
	vector<Card*> dropP1Z1, dropP1Z2, dropP1Z3, dropP1Z4;
	vector<Card*> dropP2Z1, dropP2Z2, dropP2Z3, dropP2Z4;

	void ReShuffle();	//Shuffles used cards in Discard pile back into Deck
	void CreateDeck();	//Deck Constructor
	Card* Draw();		//Returns a card from top of deck
	Field();
	~Field();
};

#endif