//
//this function contral one round of bet,
//for example preflop round of bet, which is the first round of bet
//or river bet, the last round of bet
//

#ifndef PG_GameFlow_h
#define PG_GameFlow_h

#include "PokerPlayer.h"
#include "CalculateHand.h"
#include "CompareTwo.h"
#include <map>
#include <vector>

//this function checks is every player has bet equal to the max bet on table,
//otherwise the player should fold
//
//if every player bet the same, or all-in, this function return true
//then new card comes then a new round of bet start
bool checkReady(vector<int> playerbet,map<int,int> playerleft,int maxposition);

//control the round of bet
void gameFlow(vector<PokerPlayer> &players,int SBposition, int &pot,bool ifpreflop,
              map<int,int> &playerleft,vector<int> &playerbet,bool &ifeveryAllin);


#endif
