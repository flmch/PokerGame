
#ifndef PG_DistributePot_h
#define PG_DistributePot_h

#include "PokerPlayer.h"
#include "CompareTwo.h"
#include "CalculateHand.h"
#include "Display.h"
#include <map>
#include <vector>

void printHandLevel(int l);

//sum of all in playergbet array
int sumofbet(vector<int> playerbet);

//distribute money to players if there are more than one players
void distributePot(map<int,int> playerleft, int &pot, vector<PokerPlayer> &players,vector<int> &playerbet,
                   vector<string> board, int &totalMoney);

#endif
