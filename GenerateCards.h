//generate a deck of card randomly

#ifndef PG_GenerateCards_h
#define PG_GenerateCards_h

#include <vector>
#include <string>
#include "PokerPlayer.h"

//all the number occurs on a deck of card
const char cardnumber[13]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
//all color on a deck of card
//h: heart
//s: spade
//c: club
//d; diamond
const char cardcolor[4]={'h','s','c','d'};

void shuffleCardDeck(vector<string> &deck); //shuffle cards

//following function not in use any more
void GetNewCards(vector<string> &deck,PokerPlayer &p); //take two cards from vector, then delete those two cards

#endif
