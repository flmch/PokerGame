//
//these functions are used to display some element in the game

#ifndef PG_Display_h
#define PG_Display_h
#include "PokerPlayer.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//print banner at beginning
void startBanner();

//print game regulations
void gameNotes();

//print position of dealer for a round of game
void dealerPostionDiaplay(vector<PokerPlayer> players, int round);

//display the card on board
void displayCardonBoard(vector<string> c,int stage);

#endif
