//Player.cpp

#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

Player::Player(string tName, int Y)
{
	name = tName;
	dropped51 = false;
	turn = false;
	handY = Y;
	
}

//The player adds a card to their hand
void Player::DrawCard(Card *tCard)
{
	hand.push_back(tCard);	//Push the card into the hand vector
	UpdateHand();
}

//Player Discards a single card into Discard pile
void Player::Discard(stack<Card*> &DiscardPile)
{
	for(handIt = hand.begin(); handIt < hand.end(); handIt++)	//Search through hand
	{
		if((*handIt)->selected)		//Check for selected card
		{
			DiscardPile.push(*handIt);		//Copy Card to Discard Pile
			hand.erase(handIt);				//Remove card from hand
		}
	}
}

//
bool Player::ValidateDrop()
{
	vector<Card*> tVect;
	vector<Card*>::iterator tIt;
	bool SameName = false, SameSuit = false;

	//Put all selected cards into a temporary container
	for(handIt = hand.begin(); handIt < hand.end(); handIt++)		//Search hand
	{
		if((*handIt)->selected)		//Check for selected cards
		{
			tVect.push_back(*handIt);
		}
	}

	
	//Check if all the cards have the same name
	for(tIt = tVect.begin(); tIt < tVect.end(); tIt++)
	{
		const string tName = (*tIt)->GetName(); //Store first card's name
		if(!(tName == (*tIt)->GetName()))
			break;	//Break loop if a card has a different name
		if(tIt == tVect.end())
			SameName = true;
	}

	//
	for(tIt = tVect.begin(); tIt < tVect.end(); tIt++)
	{
		const string tSuit = (*tIt)->GetSuit(); //Store first card's suit
		if(!(tSuit == (*tIt)->GetSuit()))
			break;	//Break loop if card has a different suit
		if(tIt == tVect.end())
			SameSuit = true;
	}

	//Cards are being dropped as "Of a Kind"
	if(SameName && !SameSuit)
		return true;

	//Cards are being dropped as "Sequential"
	else if(!SameName && SameSuit)
	{
		vector<int> tValues;
		vector<int>::iterator tValIt;

		//Extract only card number from cards into temporary storage
		for(tIt = tVect.begin(); tIt < tVect.end(); tIt++)
		{
			tValues.push_back((*tIt)->GetNum());
		}

		//Sort Card Numbers
		sort(tValues.begin(), tValues.end());
		int Start = *tValues.begin();

		//Check if each card is sequential with no gaps between card number
		for(tValIt = tValues.begin(); tValIt < tValues.end(); tValIt++)
		{
			if(Start == *tValIt)
				Start++;
			else
				return false; //Not valid drop
		}
		return true;	//Drop is sequential and validated
	}

	else
		return false;	//Not valid drop
}

//Player drops Cards into Drop Zones
void Player::Drop(vector<Card*> &DropZone)
{
	if(ValidateDrop())
	{
		for(handIt = hand.begin(); handIt < hand.end(); handIt++)		//Search hand
		{
			if((*handIt)->selected)		//Check for selected cards
			{
				DropZone.push_back(*handIt);	//Copy card to Drop Zone
				hand.erase(handIt);				//Remove card from hand
			}
		}
	}
}

void Player::UpdateHand()
{
	int i = 0;
	for(handIt = hand.begin(); handIt < hand.end(); handIt++)
	{
		i++;
		int NewX;
		NewX = 600/hand.size() * i;
		(*handIt)->Reposition(NewX+150, handY);
		(*handIt)->UpdateFace(turn);
	}
}

void Player::ShowHand()
{
	
	for(handIt = hand.begin(); handIt < hand.end(); handIt++)
	{
		
		(*handIt)->SpriteAnimate();
		(*handIt)->DrawFrame();
	}
}