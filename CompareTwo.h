//this function is used to compare two players hand

#ifndef PG_CompareTwo_h
#define PG_CompareTwo_h

#include "CalculateHand.h"
#include "PokerPlayer.h"

//return 1 if p1 win
//return 0 if tie
//return 2 if p1 lose
int compareTwo(vector<string> board, PokerPlayer p1, PokerPlayer p2);


#endif
