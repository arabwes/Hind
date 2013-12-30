//Field.cpp

#include "Field.h"

Field::Field()
{
	for(int l = 1; l <= 2; l++)
	{
		for(int i = 0; i < 52; i++)
		{
			string tFName, tName, tSuit, tFile, tBack;
			int tVal, tNum;

			//Assign Suit to cards
			if(i < 13)
				tSuit = "Club";
			else if(i < 26)
				tSuit = "Diamond";
			else if(i < 39)
				tSuit = "Heart";
			else if(i < 52)
				tSuit = "Spade";
		
			//Assign values and names to cards
			switch(i%13)
			{
			case 1:
				tFName = "Ace of " + tSuit;
				tName = "Ace";
				tVal = 10;
				tNum = i;
				break;
			case 2:
				tFName = "2 of " + tSuit;
				tName = "2";
				tVal = 2;
				tNum = i;
				break;
			case 3:
				tFName = "3 of " + tSuit;
				tName = "3";
				tVal = 3;
				tNum = i;
				break;
			case 4:
				tFName = "4 of " + tSuit;
				tName = "4";
				tVal = 4;
				tNum = i;
				break;
			case 5:
				tFName = "5 of " + tSuit;
				tName = "5";
				tVal = 5;
				tNum = i;
				break;
			case 6:
				tFName = "6 of " + tSuit;
				tName = "6";
				tVal = 6;
				tNum = i;
				break;
			case 7:
				tFName = "7 of " + tSuit;
				tName = "7";
				tVal = 7;
				tNum = i;
				break;
			case 8:
				tFName = "8 of " + tSuit;
				tName = "8";
				tVal = 8;
				tNum = i;
				break;
			case 9:
				tFName = "9 of " + tSuit;
				tName = "9";
				tVal = 9;
				tNum = i;
				break;
			case 10:
				tFName = "10 of " + tSuit;
				tName = "10";
				tVal = 10;
				tNum = i;
				break;
			case 11:
				tFName = "Jack of " + tSuit;
				tName = "Jack";
				tVal = 10;
				tNum = i;
				break;
			case 12:
				tFName = "Queen of " + tSuit;
				tName = "Queen";
				tVal = 10;
				tNum = i;
				break;
			case 0:
				tFName = "King of " + tSuit;
				tName = "King";
				tVal = 10;
				tNum = 13;
				break;
			}
		
			//Create Filename of each card
			if(i <= 13)
				ConcatenateString(tFile, "ArtAssets\\c", ".png", i%13);
			else if(i <= 26)
				ConcatenateString(tFile,"ArtAssets\\d", ".png", i%13);
			else if(i <= 39)
				ConcatenateString(tFile,"ArtAssets\\h", ".png", i%13);
			else if(i <= 52)
				ConcatenateString(tFile,"ArtAssets\\s", ".png", i%13);
			//The filename to the 
			if(l == 1)
				tBack = "ArtAssets\\b1fv.png";
			else if(l == 2)
				tBack = "ArtAssets\\b2fv.png";

			Card *tCard = new Card(tFName, tName, tSuit, tVal, tNum, tFile, tBack);	//Create the Card
			tCard->Reposition(455, 316);
			if(l == 1)
				cardList[i] = tCard;	//Place card into Card list
			else if(l == 2)
				cardList[52 + i] = tCard;	//Place card into Card list
		}
	}
}

Field::~Field()
{
}
//Reshuffles all the cards in the discard pile (except top card) back into the deck
void Field::ReShuffle()
{
	vector<Card*> tList;		//torary vector to hold Cards in the discard pile 
	//Card *tCard;
	Card *tTop;				//torary variable to hold top card

	tTop = discardPile.top();	//Copy Top card into torary holder
	discardPile.pop();				//Erase top card
	
	//Push remaining cards in Discard pile into tList
	while(!discardPile.empty())
	{
		tList.push_back(discardPile.top());	//Copy current top card into tList
		//tCard = discardPile.top();
		discardPile.pop();						//Erase current top card
		//delete tCard;
	}
	
	discardPile.push(tTop);		//Put the torary Card holder back into discard pile
	
	//Shuffle cards in List
	for(int i = 0; i < 200; i++)
	{
		int tL = rand()%103 + 1;
		int tR = rand()%103 + 1;

		//Possible change needed. See Createdeck()
		iter_swap(tList.begin()+tL, tList.begin()+tR);
	}

	//Push List back into the deck
	for(int i = 0; i < 103; i++)
	{
		deck.push(tList[i]);
	}
}

void Field::CreateDeck()
{
	//Swap cards in list
	for(int i = 0; i < 200; i++)
	{
		Card *t;
		int tL = rand()%103 + 1;
		int tR = rand()%103 + 1;
		//iter_swap(cardList[tL], cardList[tR]);
				
		t = cardList[tR];
		cardList[tR] = cardList[tL];
		cardList[tL] = t;
	}

	//Push cards into deck
	for(int i = 0; i < 104; i++)
	{
		deck.push(cardList[i]);
	}
}

Card* Field::Draw()
{
	//Removes card from top of the deck and returns it
	Card *tCard;
	tCard = deck.top();
	deck.pop();

	return tCard;
}